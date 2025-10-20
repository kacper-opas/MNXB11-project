This folder contains a tarball `datasets.tgz` with SHMI open data datasets.

To extract the files, run

```console
tar zxvf datasets.tgz
```

The meteorological data used in this project has been downloaded from 
the official "SMHI - Sveriges meteorologiska och hydrologiska institut"
website, <https://www.smhi.se>

The files were downloaded at the page:
<https://www.smhi.se/data/meteorologi/ladda-ner-meteorologiska-observationer/#param=airtemperatureInstant,stations=core>

They represent the _air temperature_ collected by a given station, excluding 
the last three months at the time these datasets where downloaded.

The filenames are the same as the original from SMHI but the 
filename has been suffixed with `_Cityname` to match the city name, for ease of use. 
Mind that in some cities there are more than one station, 
the filename alone does not clarify which station.

As a bonus we included some of the oldest historical data for Uppsala that 
has a different format and it has been corrected to give a more accurate 
picture of the area's climate change. 
It was the inspiration for the first course project in 2013.
It has been downloaded from <https://www.smhi.se/data/meteorologi/temperatur/uppsalas-temperaturserie-1.2855> which contains an interesting historical reading.

The content of the files has been left untouched.

The use of this data is covered by the statements at this link:
<https://www.smhi.se/data/oppna-data/information-om-oppna-data/villkor-for-anvandning-1.30622>

If you wish you can download additional data from SMHI provided that you follow their Terms Of Use.
