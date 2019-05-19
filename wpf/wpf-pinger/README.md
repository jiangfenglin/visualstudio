# wpf-pinger

WPF project for check ping response a list of ip address each X seconds.

![alt text](http://patovega.com/github/imagenes/wpf-pinger/pinger.jpg)

# About this project

* WPF Project using C#
* .Net 4.6

## Change time interval of ping

* change the value of "PingTime" setting in WPF_Pinger.exe.config, this value must be numeric. ( 1 sec = 1000, 60 sec = 60000, number represents a milisecond).

      <WPF_Pinger.Pinger>
                  <setting name="PingTime" serializeAs="String">
                      <value>15000</value>
                  </setting>
       </WPF_Pinger.Pinger>



### Run wpf-pinger 
You must add the xml file in the executable folder and add names and ip address childs to XML.


