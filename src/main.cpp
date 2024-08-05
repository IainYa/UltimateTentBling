#include <string>
#include <SPI.h>
#include <hardwareConfig.h>
#include <UltimateTentBling.h>

//#include <vaisala_rs41.h>



std::string gps = "", val = "";
int timePart, latPart, lonPart;
bool fix = 0, locChanged = 0;

void readGPS();
void parseGPS();
void updateSchedule();

void setup() {
  setupPins();
  status_green_led(0);
  status_red_led(0); 
  
  Serial1.begin(9600); //GPS
  Serial3.begin(9600); 

  reset_gps();
   
  delay(1000);  
}

void loop() 
{
  readGPS();

  if(locChanged)
  {
    updateSchedule();
  }

  
}

void readGPS()
{
  if (Serial1.available() > 0)
  {
    char c = Serial1.read();
    //Serial3.write(c);
    if (c != '\n')
    {
      gps += c;
    }
    else
    {
      if (gps.substr(0,6) == "$GPGGA")
      {
        Serial3.write("LOCATION - ");
        Serial3.write(gps.c_str());
        Serial3.write("\n");
        parseGPS();
      }
      gps.clear();

    }
  }
}

void parseGPS()
{
  std::string tim, lat, latdir, lon, londir, fixed;
  float latMin, lonMin;
  int start, len, latPartNew, lonPartNew;
  char output[100];
  //char tim[9], lat[20], latdir[1], lon[20], londir[1], fixed[1];
  
  start = gps.find(",",6)+1;
  len = gps.find(",",start) - start;
  tim = gps.substr(start,len);
  Serial3.write("Time:   ");
  Serial3.write(tim.c_str());
  Serial3.write("\r\n");

  start = gps.find(",",start)+1;
  len = gps.find(",",start) - start;
  lat = gps.substr(start,len);
  Serial3.write("Lat:    ");
  Serial3.write(lat.c_str());
  Serial3.write("\r\n");

  start = gps.find(",",start)+1;
  len = gps.find(",",start) - start;
  latdir = gps.substr(start,len);
  Serial3.write("latdir: ");
  Serial3.write(latdir.c_str());
  Serial3.write("\r\n");

  start = gps.find(",",start)+1;
  len = gps.find(",",start) - start;
  lon = gps.substr(start,len);
  Serial3.write("Lon:    ");
  Serial3.write(lon.c_str());
  Serial3.write("\r\n");

  start = gps.find(",",start)+1;
  len = gps.find(",",start) - start;
  londir = gps.substr(start,len);
  Serial3.write("londir: ");
  Serial3.write(londir.c_str());
  Serial3.write("\r\n");

  start = gps.find(",",start)+1;
  len = gps.find(",",start) - start;
  fixed = gps.substr(start,len);
  Serial3.write("fixed:  ");
  Serial3.write(fixed.compare("1") ? "No" : "Yes");
  Serial3.write("\r\n");

  if(fixed.compare("1") == 0)
  {
    status_green_led(1);
    status_red_led(0);
    start = 2;
    len = tim.find(".", start) - start;
    timePart = stoi(tim.substr(start, len));
    sprintf(output, "timepart: %d\r\n",timePart);
    Serial3.write(output);

    latMin = stof(lat.substr(2)) / 0.0006;
    latPartNew = (int)(latMin+0.5) % 50000;  // 0.5 added so that conversion to int rounds to nearest no.
    if(latdir.compare("N") == 0)
    {
      latPartNew = 50000 - latPartNew;
    }
    sprintf(output, "latPart: %d\r\n",latPartNew);
    Serial3.write(output);

    lonMin = stof(lon.substr(3)) / 0.0006;
    lonPartNew = (int)(lonMin+0.5) % 50000;  // 0.5 added so that conversion to int rounds to nearest no.
    if(londir.compare("W") == 0)
    {
      lonPartNew = 50000 - lonPartNew;
    }
    sprintf(output, "lonPart: %d\r\n",lonPartNew);
    Serial3.write(output);

    if (latPart != latPartNew || lonPart != lonPartNew)
    {
      locChanged = 1;
      status_red_led(1);
      latPart = latPartNew;
      lonPart = lonPartNew;
    }
  }
  else{
    status_green_led(0);
    status_red_led(1);
  }

}


void updateSchedule()
{
  for(int i=0; i<10000000; i++)
  {}
  status_red_led(0);
}