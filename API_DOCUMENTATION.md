# API Documentation

## Base URL
```
http://localhost:3000/api
```

## Authentication

### Login
**Endpoint:** `POST /api/login`

**Request Body:**
```json
{
  "username": "string",
  "password": "string"
}
```

**Response:**
```json
{
  "success": true,
  "message": "Login successful!"
}
```

---

## Users

### Get All Users
**Endpoint:** `GET /api/users`

**Response:**
```json
[
  {
    "id": 1,
    "username": "admin",
    "email": "admin@example.com",
    "createdAt": "2024-01-01T00:00:00.000Z"
  }
]
```

### Create User
**Endpoint:** `POST /api/users`

**Request Body:**
```json
{
  "username": "string",
  "email": "string",
  "password": "string"
}
```

---

## Devices

### Get All Devices
**Endpoint:** `GET /api/devices`

**Response:**
```json
[
  {
    "id": 1,
    "name": "Living Room Light",
    "type": "light",
    "status": "on",
    "roomId": 1
  }
]
```

### Create Device
**Endpoint:** `POST /api/devices`

**Request Body:**
```json
{
  "name": "string",
  "type": "string",
  "roomId": "number"
}
```

### Update Device
**Endpoint:** `PUT /api/devices/:id`

**Request Body:**
```json
{
  "status": "on" | "off"
}
```

### Delete Device
**Endpoint:** `DELETE /api/devices/:id`

---

## Rooms

### Get All Rooms
**Endpoint:** `GET /api/rooms`

**Response:**
```json
[
  {
    "id": 1,
    "name": "Living Room",
    "devices": []
  }
]
```

### Create Room
**Endpoint:** `POST /api/rooms`

**Request Body:**
```json
{
  "name": "string"
}
```

---

## Sensor Data

### Get Sensor Data
**Endpoint:** `GET /api/sensors-data`

**Query Parameters:**
- `type` (optional): Filter by sensor type (temperature, humidity, motion, etc.)
- `limit` (optional): Number of records to return

**Response:**
```json
[
  {
    "id": 1,
    "sensor_type": "temperature",
    "value": "24",
    "timestamp": "2024-01-01T00:00:00.000Z"
  }
]
```

### Log Sensor Data
**Endpoint:** `POST /log-sensor`

**Request Body:**
```json
{
  "sensor_type": "temperature" | "humidity" | "motion" | "fire" | "gas",
  "value": "string"
}
```

**Response:**
```json
{
  "message": "Logged successfully"
}
```

---

## Commands

### Send Command
**Endpoint:** `POST /api/commands`

**Request Body:**
```json
{
  "deviceId": "number",
  "command": "string",
  "value": "string"
}
```

**Example Commands:**
- `{ "command": "light_on" }`
- `{ "command": "ac_cool" }`
- `{ "command": "door_open" }`

---

## Logs

### Get System Logs
**Endpoint:** `GET /api/logs`

**Query Parameters:**
- `limit` (optional): Number of logs to return
- `type` (optional): Filter by log type

**Response:**
```json
[
  {
    "id": 1,
    "action": "Device turned on",
    "deviceId": 1,
    "timestamp": "2024-01-01T00:00:00.000Z"
  }
]
```

---

## WebSocket API

### Connection
**URL:** `ws://localhost:8080`

### Events

#### Client → Server
Send commands to control devices:
```json
{
  "type": "command",
  "device": "light",
  "action": "on"
}
```

#### Server → Client
Receive real-time updates:
```json
{
  "type": "sensor_update",
  "sensor": "temperature",
  "value": "24"
}
```

### Example WebSocket Client
```javascript
const ws = new WebSocket('ws://localhost:8080');

ws.onopen = () => {
  console.log('Connected to WebSocket');
  ws.send(JSON.stringify({ type: 'command', device: 'light', action: 'on' }));
};

ws.onmessage = (event) => {
  console.log('Received:', event.data);
};
```

---

## Error Responses

All endpoints may return the following error responses:

### 400 Bad Request
```json
{
  "success": false,
  "message": "Invalid request parameters"
}
```

### 401 Unauthorized
```json
{
  "success": false,
  "message": "Authentication required"
}
```

### 404 Not Found
```json
{
  "success": false,
  "message": "Resource not found"
}
```

### 500 Internal Server Error
```json
{
  "success": false,
  "message": "Server error"
}
```

---

## Rate Limiting
Currently no rate limiting is implemented. Consider adding rate limiting for production use.

## CORS
CORS is enabled for:
- `http://localhost:3000`
- `https://smarthome-five-rose.vercel.app`

Add additional origins in the `.env` file.
