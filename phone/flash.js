// Create Web Audio Context
var context = new webkitAudioContext(); 
		
// Click Event for flash button
document.getElementById('flash').addEventListener('click', function() {

	// Create oscillator sound source
	oscillator = context.createOscillator();
	
	// Connect sound to output
	oscillator.connect(context.destination);
	
	// Play Sound
	oscillator.noteOn(0);
	
	// wait 50ms
	var beep = setInterval(function() {
		// stop sound
		oscillator.noteOff(0);
		// Stop Interval
		clearInterval(beep);
	}, 50);
});