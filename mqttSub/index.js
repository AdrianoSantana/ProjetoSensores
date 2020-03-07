const mqtt = require('mqtt')
const client  = mqtt.connect('mqtt://mqtt.eclipse.org')
var topic = 'sensorLdr'

client.on('connect', function () {
  client.subscribe(topic, function (err) {
    if (err) {
      console.log('error:', err)
    }else{
      console.log('tudo certo')
      // client.publish('presence', 'Hello mqtt')
    }
  })
})
 
client.on('message', function (topic, message) {
  // message is Buffer
  console.log(message.toString())
  // client.end()
})