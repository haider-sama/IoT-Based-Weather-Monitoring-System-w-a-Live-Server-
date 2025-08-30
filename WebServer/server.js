const express = require('express');
const http = require('http');
const { Server } = require('socket.io');
const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');

const app = express();
const server = http.createServer(app);
const io = new Server(server);

const port = new SerialPort({ path: 'COM7', baudRate: 9600 });
const parser = port.pipe(new ReadlineParser({ delimiter: '\n' }));

app.use(express.static('public'));

parser.on('data', (line) => {
    console.log('Received:', line);
    io.emit('serialData', line);

    if (line.includes("Humidity:") && !line.includes("BMP")) {
        const match = line.match(/Humidity:\s*([\d.]+)/);
        if (match) io.emit('humidity', parseFloat(match[1]));
    } else if (line.includes("DHT Temp:")) {
        const match = line.match(/DHT Temp:\s*([\d.]+)/);
        if (match) io.emit('dhtTemp', parseFloat(match[1]));
    } else if (line.includes("BMP180 Temp:")) {
        const match = line.match(/BMP180 Temp:\s*([\d.]+)/);
        if (match) io.emit('bmpTemp', parseFloat(match[1]));
    } else if (line.includes("Pressure:")) {
        const match = line.match(/Pressure:\s*([\d.]+)/);
        if (match) io.emit('pressure', parseFloat(match[1]));
    } else if (line.includes("Altitude:")) {
        const match = line.match(/Altitude:\s*([\d.]+)/);
        if (match) io.emit('altitude', parseFloat(match[1]));
    } else if (line.includes("Rain Value:")) {
        const match = line.match(/Rain Value:\s*([\d.]+)/);
        if (match) io.emit('rain', parseFloat(match[1]));
    }
});

server.listen(3000, () => {
    console.log('Server listening on http://localhost:3000');
});
