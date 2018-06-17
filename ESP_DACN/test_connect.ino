#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <string.h>
// Cập nhật thông tin
// Thông tin về wifi
#define ssid "Huy Nam Quan"
#define password "@123456789"
// Thông tin về MQTT Broker
#define mqtt_server "m12.cloudmqtt.com" // Thay bằng thông tin của bạn
#define mqtt_topic_pub "quanphan"   //Giữ nguyên nếu bạn tạo topic tên là demo
#define mqtt_topic_sub "quanphan"
#define mqtt_user "esp8266"    //Giữ nguyên nếu bạn tạo user là esp8266 và pass là 123456
#define mqtt_pwd "123456"

const uint16_t mqtt_port = 14354; //Port của CloudMQTT

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[100];

void setup() 
{
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port); 
  client.setCallback(callback);
}
// Hàm kết nối wifi
void setup_wifi() 
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
// Hàm call back để nhận dữ liệu
void callback(char* topic, byte* payload, unsigned int length) 
{
  //Serial.print("Message arrived [");
  //Serial.print(topic);
  //Serial.print("] ");
  for (int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  
}
// Hàm reconnect thực hiện kết nối lại khi mất kết nối với MQTT Broker
void reconnect() 
{
  // Chờ tới khi kết nối
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Thực hiện kết nối với mqtt user và pass
    if (client.connect("ESP8266Client",mqtt_user, mqtt_pwd)) {
      Serial.println("connected");
      // Khi kết nối sẽ publish thông báo
      client.publish(mqtt_topic_pub, "ESP_reconnected");
      // ... và nhận lại thông tin này
      client.subscribe(mqtt_topic_sub);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Đợi 5s
      delay(5000);
    }
  }
}
void loop() 
{
  // Kiểm tra kết nối
  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop();
  // Sau mỗi 2s sẽ thực hiện publish dòng hello world lên MQTT broker
  //long now = millis();
  //if (now - lastMsg > 2000) 
  //{
    //lastMsg = now;
    //value = analogRead(A0);
    int i=0;
   while(Serial.available()>0)
   {
      msg[i]=Serial.read();
      i++;
    }
    //snprintf (msg, 75, "ADC #%ld", value);;
    //Serial.print("Publish message: ");
    //callback(mqtt_topic_sub,data,20);
    //Serial.println(msg);
    if(i!=0)
    {
      client.publish(mqtt_topic_pub, msg);
      for(int j=0;j<100;j++)
      {
          msg[j]=0x00;
      }
     }
}
