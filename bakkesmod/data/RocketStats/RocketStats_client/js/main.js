// Enable debug
window.console_debug = true;

// To request all statistics without an event
//window.Send2RocketStats("request");

// Events returning all statistics
document.addEventListener("RocketStats_GameState", async event => {
	event = event.detail;
	const Name = event.name;
	const Stats = event.data.Stats;

	Object.keys(Stats).forEach(key => {
		let target = document.querySelector(`[rocketstats="${key}"]`);
		if (target)
		{
			let value = Stats[key];
			if (typeof(value) == "number")
				value = value.toFixed(key.indexOf("MMR") ? 0 : 2);

			target.innerText = value;
		}
	});
});

// Game Notifications
document.addEventListener("RocketStats_StatEvent", async event => {
	event = event.detail;
	const Name = event.name;
	const Data = event.data;

	let elem = document.createElement("div");
	elem.classList.add("pop-event", "stat-event");
	elem.style.color = "#0c0";
	elem.innerText = `${Name}[${Data.Points}pts]`;

	document.querySelector(".container").appendChild(elem);
	setTimeout(() => {
		elem.remove();
	}, 10000);
})

// All notifications displayed in the upper right corner of the game
document.addEventListener("RocketStats_TickerMessage", async event => {
	event = event.detail;
	const Name = event.name;
	const Data = event.data;

	let selem = document.createElement("span");
	selem.innerText = `Receiver=${Data.Receiver} Victim=${Data.Victim}`;

	let elem = document.createElement("div");
	elem.classList.add("pop-event", "ticket-message");
	elem.style.color = "#cc0";
	elem.innerText = `${Name}[${Data.Points}pts]:`;

	elem.appendChild(selem);
	document.querySelector(".container").appendChild(elem);

	setTimeout(() => {
		elem.remove();
	}, 10000);
});

//
document.addEventListener("RocketStats_Boost", async event => {
	event = event.detail;
	const Data = event.data;

	if (typeof(Data) === "number")
	document.querySelector(".boost").innerText = ((Data >= 0) ? `${Data}%` : "Disabled");
});
