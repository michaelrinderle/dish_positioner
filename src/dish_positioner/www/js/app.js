////enum static_rest_types
////{
////  ANGLE = 0,
////  LIMITS_SET = 1,
////  ANGLE_EXTEND = 2,
////  ANGLE_RETRACT = 3,
////  TRAIN = 4,
////  SCAN_RANGE = 5,
////};

// typedef int TRUE = 0;
// typedef int FALSE = 1;

var base_url = '/arduino/satellitepositioner/';
var position_binding = '#position';
var range_status_binding = '#range-status';
window.loading = false;

$(document).ready(() => {
	isTrainComplete();
});

// listener for setting angle manually
$(".set-angle").click(function(){
	if(window.loading) return;
	window.loading = true;
	setAngle($(this).attr('id'));
	window.loading = false;
});

// listener to train positioner 
$(".train-range").click(function(){
	if(window.loading) return;
	window.loading = true;
	scanRange();
	window.loading = false;
});

// listener to make one pass through limits
$(".scan-range").click(function(){
	if(window.loading) return;
	window.loading = true;
	scanRange();
	window.loading = false;
});

// check if limits are set
function isTrainComplete(){
	$.get(base_url + '4', function( data ) {
		$(position_binding).html(data);	
		if(data == "1"){
			alert("Limits not set yet!");
			return;
		}
		else
		    getAngle();
	});
}

function getAngle(){
	$.get(base_url+'0', function( data ) {
		$(position_binding).html(data);	
	});
}

function setAngle(direction){
	var uri = (direction == 'angle-extend') ? base_url + '1' : base_url + '2';
	$.get(uri, function( data ) {
		$(position_binding).html(data);	
	});
}

function trainRange(){
	$.get(base_url + '3', function( data ) {
		$(range_status_binding).html(data);	
	});
}

function scanRange(){
	$.get(base_url + '5', function( data ) {
		$(range_status_binding).html(data);	
	});
}