// giving value to the time
const study_time = 25 * 60;
const break_time = 5 * 60;

// for character sprite gif

const gif_study = "";
const gif_break = "";
const gif_poked = "";

// dialouge for speech bubble

const dialouge_tier = {
    level1: ["Let's get to work.", "Focus.", "Hmph."],
    level3: ["Good job.", "See? I knew you can do it.", "I trust that you are following along?"],
    level5: ["You are catching up well.", "Well Done.", "You are improving well."]

};

// xp bar

let affection_xp = parseInt(localStorage.getItem('companionXP')) || 0;
let affection_level = parseInt(localStorage.getItem('companionLevel')) || 1;
const XP_per_Level = 10;

let timeLeft = study_time;
let timerId = null;
let isCurrentlyStudy = true;
let isPoked = false;

// ui elements

const timeDisplay = document.getElementById('time-display');
const statusLabel = document.getElementById('status-label');
const characterImg = document.getElementById('character-img');
const bubble = document.getElementById('speech-bubble');
const achievementBox = document.getElementById('achievement-box')

function updateTime() {
    let minutes = Math.floor(timeLeft / 60);
    let seconds = timeLeft % 60;
    timeDisplay.textContent = `${minutes.toString().padStart(2, '0')}:${seconds.toString().padStart(2, '0')}`;
}

function updateStatusUI() {
    let levelXP = affection_xp % XP_per_Level;
    let percentage = (levelXP / XP_per_Level) * 100;

    document.getElementById('xp-bar-fill').style.width = `${percentage}%`;
    document.getElementById('level-badge').textContent = `Affection Lvl ${affection_level}`;
    document.getAnimations('total-points-text').textContent = `${levelXP} / ${XP_per_Level} XP (Total: ${affection_xp})`;

    checkMilestoneBadge();
}

function startTimer() {
    if (timerId !== null) return;
    timerId = setInterval(() => {
        timeLeft--;
        updateDisplay();
        if (timeLeft <= 0) {
            clearInterval(timerId);
            timerId = null;
            switchMode();
        }
    }, 1000);
}

function pauseTimer() {
    clearInterval(timerId);
    timerId = null;
}

function resetTimer() {
    pauseTimer();
    isCurrentlyStudy = true;
    timeLeft = study_time;
    statusLabel.textContent = gif_study;
    updateDisplay();
}

function switchMode() {
    if (isCurrentlyStudy) {
        // earn 2 xp when finished a full session
        affection_xp += 2;
        let newLevel = Math.floor(affection_xp / XP_per_Level) + 1;
        if (newLevel > affection_level) {
            affection_level = newLevel;
            triggerAchievementNotification(`Level UP! Level ${affection_level} Unlocked!`);
        }
        localStorage.setItem('companionXP', affection_xp);
        localStorage.setItem('companionLevel', affection_level);
        updateStatusUI();

        isCurrentlyStudy = false;
        timeLeft = break_time;
        statusLabel.textContent = "Hard Work deserve a break.";
        characterImg.src = gif_break;
    } else {
        isCurrentlyStudy = true;
        timeLeft = study_time;
        statusLabel.textContent = "Let continue where we left off.";
        characterImg.src = gif_study;
    }
    updateDisplay();
    startTimer();
}

// tap/click action

function pokeCharacter() {
    if (isPoked) return;
    isPoked = true;

    let dynamicPhrases = dialouge_tier.level1;
    if (affection_level >= 5) {
        dynamicPhrases = dialouge_tier.level5;
    } else if (affection_level >= 3) {
        dynamicPhrases = dialouge_tier.level3;
    }
    const randomIndex = Math.floor(Math.random() * dynamicPhrases.length);
    bubble.textContent = dynamicPhrases[randomIndex];

    bubble.classList.remove('hidden-bubble');
    characterImg.src = gif_poked;

    setTimeout(() => {
        bubble.classList.add('hidden-bubble');
        characterImg.src = isCurrentlyStudy ? gif_study : gif_break;
        isPoked = false;
    }, 2000);
}

// achivementn logic

function triggerAchievementNotification(message) {
    achievementBox.textContent = message;
    achievementBox.style.display = "block";
    setTimeout(() => {
        achievementBox.style.display = "none";
    }, 5000);
}

function checkMilestoneBadge() {
    if (affection_level === 3 && !localStorage.getItem('badge_lv3')) {
        localStorage.getItem('badge_lv3', true);
        triggerAchievementNotification("Achievement: Soften Heart");
    }
    if (affection_level === 5 && !localStorage.getItem('badge_lv5')) {
        localStorage.getItem('badge_lv5', true);
        triggerAchievementNotification("Achievement: Trusted Friend");
    }
}

// toggle text changes with bootstraps
function toggleMusicButtonText() {
    const toggleBtn = document.getElementById('toggle-music-btn');
    //time delay for double check
    setTimeout(() => {
        const musicPanel = document.getElementById('musicCollapse');
        if (musicPanel.classList.contains('show')) {
            toggleBtn.textContent = "Hide Music Panel";
        } else {
            toggleBtn.textContent = "Show Music Panel";
        }
    }, 50);
}

// data ui sync + execution?
updateDisplay();
updateStatusUI();