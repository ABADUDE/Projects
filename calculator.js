let display = document.getElementById('display');
let memory = 0;

// Append input to display
function appendToDisplay(value) {
    display.value += value;
}

// Clear display
function clearDisplay() {
    display.value = '';
}

// Calculate result
function calculateResult() {
    try {
        // Replace ^ with ** for exponentiation
        let expression = display.value.replace(/\^/g, '**');
        // Evaluate trigonometric functions in radians
        expression = expression.replace(/sin\(/g, 'Math.sin(');
        expression = expression.replace(/cos\(/g, 'Math.cos(');
        expression = expression.replace(/tan\(/g, 'Math.tan(');
        expression = expression.replace(/log\(/g, 'Math.log10(');
        expression = expression.replace(/√/g, 'Math.sqrt(');
        // Replace π with Math.PI
        expression = expression.replace(/π/g, 'Math.PI');
        display.value = eval(expression);
    } catch (error) {
        display.value = 'Error';
    }
}

// Memory functions
function memoryAdd() {
    const currentValue = parseFloat(display.value);
    if (!isNaN(currentValue)) {
        memory += currentValue;
    }
}

function memorySubtract() {
    const currentValue = parseFloat(display.value);
    if (!isNaN(currentValue)) {
        memory -= currentValue;
    }
}

function memoryRecall() {
    display.value = memory.toString();
}

function memoryClear() {
    memory = 0;
}

// Square root
function calculateSquareRoot() {
    const value = parseFloat(display.value);
    if (!isNaN(value) && value >= 0) {
        display.value = Math.sqrt(value);
    } else {
        display.value = 'Error';
    }
}

// Backspace function
function backspace() {
    display.value = display.value.slice(0, -1);
}

// Keyboard support
document.addEventListener('keydown', (e) => {
    if (/[0-9+\-*/.^()π]/.test(e.key)) {
        appendToDisplay(e.key);
    } else if (e.key === 'Enter' || e.key === '=') {
        calculateResult();
    } else if (e.key === 'Escape') {
        clearDisplay();
    } else if (e.key === 'Backspace') {
        backspace();
    }
    // Prevent default action for these keys
    if (['Enter', '=', 'Escape', 'Backspace'].includes(e.key)) {
        e.preventDefault();
    }
});