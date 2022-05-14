// Do not touch the following
let errors = 0b11;
const connect = () => {
	let ws = new WebSocket("ws://127.0.0.1:8085");
	let debug = () => (typeof(window.console_debug) !== 'undefined' && window.console_debug);
	window.Send2RocketStats = message => ws.send(message);

	ws.onopen = () => {
		errors = 0b00;
		if (debug())
			console.log("Connected");
	};

	ws.onmessage = event => {
		try
		{
			const msg = JSON.parse(event.data);

			if (debug())
			{
				const d = new Date();
				const date = d.toLocaleDateString() + ' ' + d.toLocaleTimeString() + '.' + d.getMilliseconds();
				const name_color = "color: #ddd; text-decoration: underline;";
				const value_color = "color: #0c0";
				const date_color = "color: #cc0";
				console.log(
					`%cName:%c ${msg.name}\n%cType:%c ${msg.type}\n%cDate:%c ${date}\n%cData & States:`,
					name_color,
					value_color,
					name_color,
					value_color,
					name_color,
					date_color,
					name_color,
					msg.data, msg.states
				);
			}

			document.dispatchEvent(new CustomEvent(('RocketStats_' + msg.type), {
				//bubbles: true,
				detail: {
					name: msg.name,
					type: msg.type,
					data: msg.data,
					states: msg.states
				}
			}));

			document.dispatchEvent(new CustomEvent(('RocketStats_' + msg.name), {
				//bubbles: true,
				detail: {
					name: msg.name,
					type: msg.type,
					data: msg.data,
					states: msg.states
				}
			}));

			if (msg.name == 'State' && msg.data == 'Disconnected')
				errors = 0b11;
		}
		catch (error)
		{
			if (debug())
				console.error("Error while parsing WS data:", event.data);
		}
	};

	ws.onclose = event => {
		if (debug() && !(errors & 0b01))
			console.log("Socket closed, try reconnect...");

		errors |= 0b01;
		setTimeout(connect, 1000);
	};

	ws.onerror = event => {
		if (debug() && !(errors & 0b10))
			console.error("Socket error");

		errors |= 0b10;
		ws.close();
	};
};

connect();
