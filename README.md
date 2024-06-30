# IoT_Based_Smart_Agriculture_Model
<a href="https://en.wikipedia.org/wiki/Agrivoltaic">Photovoltaic agriculture</a>, the combination of photovoltaic power generation and agricultural activities, is a natural response to supply the green and sustainable electricity for agriculture. Photovoltaic agriculture can effectively alleviate the contradiction between more population and less land, powerfully promote the development of controlled environmental agriculture, evidently increase economic benefits of farmers, and significantly improve environment by reducing the emissions. PA farms are developed in few countries to elevate employment and fror research purposes. China is a leading player in this field.<br><br>
In this project I built a mini pa farm which uses sun tracking solar panel to effectively capture solar energy and used a soil moisture sensor along with a motor pump to water the plants if the soil gets dry and notifies the user when this happens via mail.<br><i>(As my nodemcu can only power upto 3v I used arduino uno along side to power up the modules.)</i><br><br>
<b>Components Used:</b>
<li>Arduino Uno(+ Node MCU)  [Esp8266 can be used with uno to achieve the task]
<li>LDR x2
<li>Soil Moisture Sensor
<li>Sg90 Servo Motor
<li>3-9V DC Motor Pump + tube
<li> Resistors 3.3k&#8486; x2
<li>Push Switch (SPST)
<li>Relay
<li>Power Source(9V Battery)
<li>Jumper wires
  <br><br><b>Setup:</b><br>
  <img src="https://github.com/Ruthvik-1411/IoT_Based_Smart_Agriculture_Model/blob/main/isas_setup01.jpg?raw=true" height=300 width=400>
  <img src="https://github.com/Ruthvik-1411/IoT_Based_Smart_Agriculture_Model/blob/main/isas_setup02.jpg?raw=true" height=300 width=400><br><br>
  <b>Working:</b>
  <p>The .ino code above is commented well to get a good idea of how the code works. But in simple terms, first the data from soil moisture sensor is read by the arduino. Soil moisture sensor works by applying a potential between its two electrodes. If the soil is dry then the soil acts as an insulator no charge can pass between the electrodes. But if there is enough moisture then charge passes through the soil and conducts which will change the difference between the potentials. </p>
<p> Now if the soil is very dry or if the sensor is in the air, we get a high value in the range of 800-1024, if its in wet soil or shorted then we get a low value 300-0. In order to exactly know if the soil has good moisture or not, the boundaries for our observations must be set. We calibrate the soil which is very dry(drought) and very wet(flood). Say the values are 800 for a very dry soil and 200 for very wet soil. So dry indicates that our soil has 0% water and wet indicates 100% moisture or the reverse can also be taken. These analog values that we obtained should then be mapped to the range we want such as (200,800)->(0,100) or (100,0) as required.</p>
<p> A threshold moisture value is set and if the moisture drops below this value then the motor pump is actuated and the plants are watered. When this happens a the moisture value is sent to thingspeak channel and is analyzed there. The motor pump can also be actuated without all this. The user can simply ON the SPST switch and water the plants.</p>
<p> The value of moisture is sent to the thingspeak channel and entered into the respective field. A similar threshold condition is evaluated and by using the services of thingspeak like Thingshttp and React we can trigger an IFTTT event which was previously created to notify the user when the threshold is crossed.</p>
  <b>IFTTT</b> is a service that allows the user to trigger a previously built event like sending a mail or adding data to sheets etc. It uses webhooks request to trigger the event and when the http request is triggered the event gets triggered.<br>
  <b>React</b>, the http request that the IFTTT webhook recieves is triggered by the react. The http request is added to the Things http and react uses it from here. In React we set the logical condition like if value in the field is <30 or the string contains &^* characters and if met it trigger this request. It can be set to trigger everytime the condition is met or the first time or every 10 times etc.<br>
  <b>Thingshttp</b> is a service offered by thingspeak to connect varies apis to thingspeak platform. In the thingshttp app the request of needed api is added and mode like GET or POST are given. It is then used by other services like React. In this case React triggers the GET Request which in turn triggers the event and sends a mail to user.<br><br>
  <img src="https://github.com/Ruthvik-1411/IoT_Based_Smart_Agriculture_Model/blob/main/isas_ts01.jpg?raw=true" height=300 width=350>
  <img src="https://github.com/Ruthvik-1411/IoT_Based_Smart_Agriculture_Model/blob/main/isas_mail.jpg?raw=true" height=300 width=450>
  <br><br>
  The other block of the code reads the values of LDRs from the arrangement and aligns the mechanical setup using servo motor so that the solar panel is always directed towards maximum illumination. This block is the <a href="https://github.com/Ruthvik-1411/Sun_Following_Solar_Panel"> Sun tracking solar panel</a> that was built before.<br><br>
  YouTube Demo Video Link: https://youtu.be/6Th6-AA5KNU
