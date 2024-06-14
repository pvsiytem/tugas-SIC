from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/post-data', methods=['POST'])
def post_data():
    if request.is_json:
        data = request.get_json()
        temperature = data.get('temperature')
        humidity = data.get('humidity')
        print(f"Received Temperature: {temperature}°C, Humidity: {humidity}%")
        return jsonify({"message": "Data received successfully", "status": "success"}), 200
    else:
        return jsonify({"message": "Invalid request", "status": "error"}), 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)