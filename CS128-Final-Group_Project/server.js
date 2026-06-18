const express = require('express');
const http = require('http');
const { Server } = require('socket.io');
const cors = require('cors');
const { Socket } = require('dgram');

const app = express();
app.use(cors()); // letting server accept req from any origin
app.use(express.static(__dirname));
const server = http.createServer(app);
const io = new Server(server, {
    cors: {
        origin: "*", // allow any origins
        methods: ["GET", "POST"]
    }
});

// shared state of timer

let timerState = {
    timerLeft: 25 * 60,
    isRunning: false,
    isCurrentStudySession: true,
    affection_xp: 0,
    affection_level: 0
};

let timerInterval = null;

function startServerTimer() {
    if (timerInterval) return; // timer is already running
    timerInterval = setInterval(() => {
        if (timerState.timerLeft > 0) {
            timerState.timerLeft--;
            io.emit('timerUpdate', timerState);
        } else {
            clearInterval(timerInterval);
            timerInterval = null;
            switchServerMode();
        }
    }, 1000);
}

function pauseServerTimer() {
    if (timerState.isCurrentStudySession) {
        timerState.affection_xp += 2;
        timerState.affection_level = Math.floor(timerState.affection_xp / 10) + 1;
        timerState.isCurrentStudySession = false;
        timerState.timerLeft = 5 * 60; // 5 min break here
    } else {
        timerState.isCurrentStudySession = true;
        timerState.timerLeft = 25 * 60; // 25 min study is back on track
    }
    timerState.isRunning = true;
    io.emit('timerUpdate', timerState);
    startServerTimer();
}

function switchServerMode() {
    if (timerState.isCurrentStudySession) {
        timerState.affection_xp += 2;
        timerState.affection_level = Math.floor(timerState.affection_xp / 10) + 1;
        timerState.isCurrentStudySession = false;
        timerState.timerLeft = 5 * 60; // 5 min break here
    } else {
        timerState.isCurrentStudySession = true;
        timerState.timerLeft = 25 * 60; // 25 min input
    }
    io.emit('timerUpdate', timerState);
    startServerTimer();
}

// websocket connection

io.on('connection', (Socket) => {
    // send current state to new companion
    Socket.emit('timerUpdate', timerState);

    Socket.on('startTimer', () => {
        timerState.isRunning = true;
        startServerTimer();
        io.emit('timerUpdate', timerState);
    });
    Socket.on('pauseTimer', () => {
        timerState.isRunning = false;
        if (timerInterval) {
            clearInterval(timerInterval);
            timerInterval = null;
        }
        io.emit('timerUpdate', timerState);
    });
    Socket.on('resetTimer', () => {
        if (timerInterval) {
            clearInterval(timerInterval);
            timerInterval = null;
        }
        timerState.isCurrentStudySession = true;
        timerState.timerLeft = 25 * 60;
        timerState.isRunning = false;
        io.emit('timerUpdate', timerState);
    });
    Socket.on('characterPoke', (phrase) => {
        Socket.broadcast.emit('companionPoked', phrase);
    });
});

const PORT = process.env.PORT || 3000;
server.listen(PORT, () => {
    console.log(`Study Timer BackEnd running on ${PORT}`);
});