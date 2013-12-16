var url="";
var planet = 1;
var canvas = document.getElementById('myCanvas');
var ctx = canvas.getContext('2d');
var json = "";
var imageObj = new Image();
var clans = new Array();
			
function initMap(planet, url) {

	this.planet = planet;
	this.url = url;
	drawScreen();
	refresh();
}

function getRandomInt (min, max) {
	return Math.floor(Math.random() * (max - min + 1)) + min;
}

function get_clan_color(cid) {

	for (a=0; a<clans.length; a++) {
		if (clans[cid]) {
			return clans[cid];
		} 
	}
						
	var nr1 = getRandomInt(128, 256);		
	var nr2 = getRandomInt(128, 256);		
	var nr3 = getRandomInt(128, 256);		
			
	clans[cid] = 'rgba('+nr1+','+nr2+','+nr3+', 0.7)';
	return clans[cid];
}

function getSectorData() {

	if (window.XMLHttpRequest) {
		// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	} else {
		// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
			
	xmlhttp.onreadystatechange=function() {
		if (xmlhttp.readyState==4 && xmlhttp.status==200) {
		
			json = xmlhttp.responseText;
			drawScreen();
		}
	}
	
	xmlhttp.open("POST", url+"/" ,true);
	xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
	xmlhttp.send("mid=1011&eid=1&planet="+planet);
}

function getClanInfo(cid) {
	if (window.XMLHttpRequest) {
		// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	} else {
		// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
			
	xmlhttp.onreadystatechange=function() {
		if (xmlhttp.readyState==4 && xmlhttp.status==200) {
					
			var clan = eval('('+xmlhttp.responseText+')');
														
			var text = 'Name = '+clan.name+'\r\n';
				text += 'Slogan = '+clan.slogan+'\r\n';
				text += 'Won = '+clan.won+'\r\n';
				text += 'Lost = '+clan.lost+'\r\n';
				text += 'Created = '+clan.created+'\r\n';
				text += 'Last Active = '+clan.last_activity+'\r\n';
				text += 'Clan Id = '+clan.cid+'\r\n';
				text += 'Player Id = '+clan.pid+'\r\n';
				
			alert(text);
		}
	}
	
	xmlhttp.open("POST", url+"/" ,true);
	xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
	xmlhttp.send("mid=1011&eid=2&cid="+cid);
}
		
function IsInPath(event) {
	var bb, x, y
	bb = canvas.getBoundingClientRect()
	x = (event.clientX-bb.left) * (canvas.width/bb.width)
	y = (event.clientY-bb.top) * (canvas.height/bb.height)
	return ctx.isPointInPath(x,y)
}
	
function createPolygon(x,y) {

	var yoffset=4;
	var xoffset=6;
	if ((y % 2)==0) {
		xoffset+=44;
	}
			
	var poly = [	
		{x:20+(x*88)+xoffset, y:0+ (y*18)+yoffset},
		{x:46+(x*88)+xoffset, y:0+ (y*18)+yoffset},
		{x:64+(x*88)+xoffset, y:18+(y*18)+yoffset},
		{x:46+(x*88)+xoffset, y:36+(y*18)+yoffset},
		{x:20+(x*88)+xoffset, y:36+(y*18)+yoffset},
		{x:2+ (x*88)+xoffset, y:18+(y*18)+yoffset} ];	
				
	return poly;
}
				
function isPointInPolygon(x, y, pt){

	var poly = createPolygon(x,y);
		
	for(var c = false, i = -1, l = poly.length, j = l - 1; ++i < l; j = i)
		((poly[i].y <= pt.y && pt.y < poly[j].y) || (poly[j].y <= pt.y && pt.y < poly[i].y))
		&& (pt.x < (poly[j].x - poly[i].x) * (pt.y - poly[i].y) / (poly[j].y - poly[i].y) + poly[i].x)
		&& (c = !c);
				
	return c;
}	
	
function drawPologon(x, y, name, damage, cid, event) {
	
	var yoffset=4;
	var xoffset=6;
	if ((y % 2)==0) {
		xoffset+=44;
	}
		
	var poly = createPolygon(x,y);
															
	ctx.beginPath();
	ctx.moveTo(poly[0].x, poly[0].y);
	for( j=1; j<poly.length; j++ ){
		ctx.lineTo( poly[j].x , poly[j].y )
	}
	ctx.lineTo( poly[0].x , poly[0].y )
			
	ctx.lineWidth = 1;
	ctx.strokeStyle = '#000000';
	ctx.stroke();
		
	if (name) {
		ctx.fillStyle = get_clan_color(cid);
		ctx.fill();
	}
			
	/* Process event */
	if (event!=null){
		if (IsInPath(event)) {		
							
			ctx.font = '7pt Arial';
			ctx.fillStyle = 'white';
			ctx.fillText(x+' '+y , 10 , 290);
									
			ctx.fillStyle = 'rgba(0,255,255, 0.5)';
			ctx.fill();
		} 
	}			
						
	/* Enter text to Pologon */			
	ctx.font = '7pt Arial';
	ctx.fillStyle = 'white';
	ctx.fillText(name, 18+(x*88)+xoffset, 18+(y*18)+yoffset);
	if (damage>0) {
		ctx.fillText((damage*10)+'%', 24+(x*88)+xoffset, 28+(y*18)+yoffset);
	}
			
	ctx.closePath();
}	
		
function drawScreen(event) {

	ctx.clearRect(0, 0, canvas.width, canvas.height);

	imageObj.src = 'images/planet/map'+planet+'.png';
	ctx.drawImage(imageObj, 0, 0);
			
	for(x=0;x<5;x++) {
		for(y=0;y<15;y++) {
			drawPologon(x, y, "", "", 0, event);
		}
	}
					
	var obj = eval(json);
	
	if (obj) {
		for(i=0;i<obj.length;i++) {				
			color = 'rgba(255,128,128,0.5)';
			drawPologon(obj[i].x,obj[i].y, obj[i].name, obj[i].damage, obj[i].cid, event);
		}
	}
}
	
function getMousePos(canvas, evt) {
	var rect = canvas.getBoundingClientRect();
	return {
		x: evt.clientX - rect.left,
		y: evt.clientY - rect.top
	};
} 
		  
canvas.addEventListener('mousemove', function(event) {

	drawScreen(event);

}, false);
	 
canvas.addEventListener('click', function(event) {
			
	var mousePos = getMousePos(canvas, event);
			
	var obj = eval(json);
			
	if (obj) {
		for(k=0; k<obj.length; k++) {				
			if (isPointInPolygon(obj[k].x, obj[k].y, mousePos)) {
				getClanInfo(obj[k].cid);
				break;
			}
		}
	}		 
}, false);
		
		
function refresh() {
	getSectorData();
   setTimeout(refresh, 5000);
}