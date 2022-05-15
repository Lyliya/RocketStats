const	OBSWebSocket	= require('obs-websocket-js'),
		Highlight		= require('cli-highlight').highlight,
		WebSocketClient	= require('websocket').client,
		rs				= new WebSocketClient(),
		obs				= new OBSWebSocket();

let		rs_errors		= 0b00,
		obs_errors		= 0b00,
		obs_timeout		= -1,
		console_debug	= true;

function PrintError(error, title)
{
	// Called when an error occurs

	if (console_debug)
	{
		if (!error.toString().indexOf('Error: '))
			error = error.toString().substr(7);

		console.log(((title ? (title + ' ') : '') + 'error:'), error);
	}
}

function OBSConnect()
{
	obs.connect().catch(error => {
		if (console_debug && !(obs_errors & 0b10))
			PrintError(error, 'OBSWebSocket');

		obs_errors |= 0b10;
		clearTimeout(obs_timeout);
		obs_timeout = setTimeout(OBSConnect, 5000);
	});
}

function RocketStatsConnect()
{
	rs.connect('ws://localhost:8085');
}

function RocketStatsEvent(name, type, data, states, title = 'RocketStatsEvent')
{
	// Function to represent an event from the RocketStats websocket

	this.name = name;
	this.type = type;
	this.data = data;
	this.states = states;
	this.title = title;

	this.toString = () => {
		let tdata = JSON.stringify(this.data, null, 4).split('\n').join('\n    ');
		let tstates = JSON.stringify(this.states, null, 4).split('\n').join('\n    ');

		return (
			`\n${this.title}(\n` +
			`    name = ${this.name},\n` +
			`    type = ${this.type},\n` +
			`    data = ${tdata},\n` +
			`    states = ${tstates}\n` +
			`)`
		);
	};

	return this;
}


obs.on('ConnectionOpened', () => {
	obs_errors = 0b00;
	if (console_debug)
		console.log('OBSWebSocket connected');
});

obs.on('ConnectionClosed', () => {
	if (console_debug && !(obs_errors & 0b01))
		console.log('OBSWebSocket closed, try reconnect...');

	obs_errors |= 0b01;
	clearTimeout(obs_timeout);
	obs_timeout = setTimeout(OBSConnect, 5000);
});

obs.on('ConnectionError', error => {
	if (console_debug && !(obs_errors & 0b10))
		PrintError(error, 'OBSWebSocket');

	obs_errors |= 0b10;
	obs.close();
});


rs.on('connect', connection => {
	// Called when the socket is connected

	rs_errors = 0b00;
	if (console_debug)
		console.log('RocketStats connected');

	// To request all statistics without an event
	//connection.send('request');

	let RocketStats_GameState = event => {
		// Do what you want here
	};

	let RocketStats_StatEvent = event => {
		// Do what you want here
	};

	let RocketStats_TickerMessage = event => {
		// Do what you want here
	};

	let RocketStats_Boost = event => {
		// Do what you want here
	};

	let RocketStats_Default = event => {
		// Do what you want here
	};

	let RocketStats_GameWon = event => {
		let scene_name = 'Principal';
		let source_name = 'RocketStats_Won';

		obs.send('GetSceneItemProperties', { 'item': { 'name': source_name } } ).then(item => {
			obs.send('SetSceneItemProperties', { 'scene-name': scene_name, 'item': item, 'visible': true }).then(data => {
				setTimeout(() => {
					obs.send('SetSceneItemProperties', { 'scene-name': scene_name, 'item': item, 'visible': false }).then(data => {
					}).catch(err => {
						if (console_debug)
							console.log('SetSceneItemProperties:', err);
					});
				}, 3000);
			}).catch(err => {
				if (console_debug)
					console.log('SetSceneItemProperties:', err);
			});
		}).catch( err => {
			if (console_debug)
				console.log('GetSceneItemList:', err);
		});
	};

	let RocketStats_GameLost = event => {
		let scene_name = 'Principal';
		let source_name = 'RocketStats_Lost';

		obs.send('GetSceneItemProperties', { 'item': { 'name': source_name } } ).then(item => {
			obs.send('SetSceneItemProperties', { 'scene-name': scene_name, 'item': item, 'visible': true }).then(data => {
				setTimeout(() => {
					obs.send('SetSceneItemProperties', { 'scene-name': scene_name, 'item': item, 'visible': false }).then(data => {
					}).catch(err => {
						if (console_debug)
							console.log('SetSceneItemProperties:', err);
					});
				}, 3000);
			}).catch(err => {
				if (console_debug)
					console.log('SetSceneItemProperties:', err);
			});
		}).catch( err => {
			if (console_debug)
				console.log('GetSceneItemList:', err);
		});
	};

	connection.on('message', msg => {
		// Called when a message is received from the socket

		// parse event as JSON
		try
		{
			msg = JSON.parse(msg.utf8Data);
		}
		catch (error)
		{
			PrintError(error, 'RocketStats');
			return;
		}

		let event = RocketStatsEvent(
			msg.name,
			msg.type,
			msg.data,
			msg.states,
			title = msg.type
		);

		if (console_debug)
			console.log(Highlight(event.toString(), { language: 'json', ignoreIllegals: true }));

		if (eval(`typeof RocketStats_${msg.type}`) === 'function')
			eval(`RocketStats_${msg.type}`)(event);

		if (eval(`typeof RocketStats_${msg.name}`) === 'function')
			eval(`RocketStats_${msg.name}`)(event);

		if (msg.name == 'State' && msg.data == 'Disconnected')
			rs_errors = 0b11;
	});

	connection.on('close', () => {
		// Called when the socket is closed

		if (console_debug && !(rs_errors & 0b01))
			console.log('RocketStats closed, try reconnect...');

		rs_errors |= 0b01;
		setTimeout(RocketStatsConnect, 5000);
	});

	connection.on('error', error => {
		if (console_debug && !(rs_errors & 0b10))
			PrintError(error, 'RocketStats');

		rs_errors |= 0b10;
		connection.close();
	});
});

rs.on('connectFailed', error => {
	if (console_debug && !(rs_errors & 0b10))
		PrintError(error, 'RocketStats');

	rs_errors |= 0b10;
	setTimeout(RocketStatsConnect, 5000);
});


OBSConnect();
RocketStatsConnect();
