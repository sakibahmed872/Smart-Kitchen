float sensor=A3;
float gas_value;
void setup()
{

pinMode(sensor,INPUT);
Serial.begin(9600);

}

void loop()
{

gas_value=analogRead(sensor);
Serial.println(gas_value);
}
