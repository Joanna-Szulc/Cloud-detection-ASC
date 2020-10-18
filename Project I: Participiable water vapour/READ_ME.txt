Created on Tue Apr 07 16:41:54 2020

The script Compare.py with imported scripts CIMEL.py and Radiosonde.py allow to automatically calculate (or retrieve) precipitable water (in cm) from given site from AEROnet network and Norwegian Meteorological Institute radiosonde database for a given period, or from given date to the latest available data. The functionalities within the scripts are ordered into separate functions, but the default use requires just to call compare_latest() or compare_period from CIMEL.py and use it as a master function allowing to automatically retrieve the data.

The plots are made as precipitable water vs day of year and as such processing periods longer than 12 months is possible, but it will result in the multiple data points over the same days. Still downloading and calculating precipitable water from longer periods is easily available.

With good internet connection the most time consuming part is calculating precipitable water from raw radiosonde data which will happen everytime when different time period is chosen. Calculating one year of data can take around 10 minutes. When there is possiblity to plot the data from already downloaded and calculated data the script will do so, so if you wish to for some reason recalculate the data anew (for example with new min. and max. height) I recommend to simply delete .csv files for the chosen months in the directory './data/year/'.
--------------------------------------
---CIMEL.py---------------------------
Download CIMEL photometer data automatically from given AEROnet site (https://aeronet.gsfc.nasa.gov/cgi-bin/webtool_aod_v3?stage=3&region=Europe&state=Norway&site=Andenes&place_code=10) for given period, unpack to pandas dataFrameworks. Plot precipitable water (PW) in cm.

Further information on AEROnet web service: https://aeronet.gsfc.nasa.gov/print_web_data_help_v3.html

Download lev10 data by default.

--Functions list--
	- create_dir_year(year1, year2): if they don't exist function creates directories for the downloaded data called "data/{year1}/
	- leap_year(year): checks if the year is a leap year, returns True for leap year or False for other
	- is_date(year, month, day): check if given date (in string format year = 'yyyy', month = 'mm', day = 'dd') exists and is no earlier than 2005 and no further than current day
	- check_beginning_end(year1, month1, day1, year2, month2, day2): check if given period is possible, if the year2 > year1 etc
	- download_data(year1, month1, day1, year2, month2, day2, AEROnet_site_name, download, daily_averages_b): downloads and saves to .lev10 file AEROnet data for a given period (in string format year = 'yyyy', month = 'mm', day = 'dd') and site. Any other correct name of AEROnet station will work. 
Full list of stations: https://aeronet.gsfc.nasa.gov/cgi-bin/webtool_aod_v3
Download and daily_averges take boolean values True or False. Download: True - download the data and return the file_name, False - return the file_name. Daily_averages: True - download daily_averages from CIMEL data, False - download all available points
	- read_from_file(file_name): given the correct .lev10 file unpacks the data into panda DataFrame and drops all NaN values. The available data in the DataFrame are: 'Date(dd:mm:yyyy)_Time(hh:mm:ss)', 'Day_of_Year', 'Precipitable_Water(cm)', 'AERONET_Instrument_Number', 'AERONET_Site_Name', 'Site_Latitude(Degrees)', 'Site_Longitude(Degrees)', 'Site_Elevation(m)'. Full data is available in the lev.10 file
	- run_CIMEL(year1, month1, day1, year2, month2, day2, AEROnet_site_name, daily_averages): automatically tries to open the data from file or downloads the missing data
	- plot_CIMEL(data, file_name): plots the Precipitable Water vs Day of Year. Saves the plot as .png and the data for plot as .csv. Automatically describes the site, period and if it's daily average or all points.
-------------------------------------------
-------------------------------------------

-------------------------------------------
---Radiosonde.py---------------------------
Download radiosonde data automatically from any given MET station (https://thredds.met.no/thredds/catalog/remotesensingradiosonde/catalog.html) for given period, unpack to pandas dataFrameworks. Calculate integrated water vapor (IWV) in kg/cm^2 and precipitable water (PW) in cm using Buck equation over water to estimate the saturated water pressure based on the measured dew point temperature and using ideal gas law as an estimate of water vapour mass, plot it against day of the year.

--Functions list--
	- create_dir_year(year1, year2): if they don't exist function creates directories for the downloaded data called "data/{year1}/. Void.
	- leap_year(year): checks if the year is a leap year. Returns True for leap year or False for other.
	- is_date(year, month, day): check if given date (in string format year = 'yyyy', month = 'mm', day = 'dd') exists and is no earlier than 1994 and no further than current day. Returns True for correct date, raises error for incorrect one.
	- check_beginning_end(year1, month1, day1, year2, month2, day2): check if given period is possible, if the year2 > year1 etc. Returns True for correct date, raises error for incorrect one.
	- download_period(year1, month1, year2, month2, download, MET_site_name): this function decomposes given period into one year chunks and calls download_one_year(). Returns a list of lists 'file_names' containing paths to all downloaded files needed to calculate given period.
	- get_period(year, month): exchanges year and a month for a string representing one month period as stored in MET database (for example May 2019 would be: 20190430-20190531). Returns this string called "period".
	- download_one_year(year, month1, month2, download, MET_site_name): decomposes downloading data from the same year into downloading specific months and calling get_period() creates url's for those months. If download argument is True it calls download_one_month() for each month, else it just returns the file names. Returns a list of (string) file names containing downloaded file names from the same year.
	- download_one_month(file_url, file_name): downloads one month of data from MET database and saves it as file_name.nc. Void.
	- get_entries(fh): Returns number of entries in a netCDF file (number of launches during the month in this case).
	- prepare_data(fh, day, MET_site_name): unpacks netCDF file into panda DataFrame, takes from the file: geopotential_height [m], pressure [hPa], temperature [K], relative_humidity [%], dew_point [K] and its units as well as date, time, latitude, longtitude and name of the launch site. Other data could be drawn from netCDF file with small modifications (for full list see the netCDF file with a viewer on MET database website). Returns a tuple: [data, launch_date, launch_date_day, launch_place] with data being DataFrame containing all the measurements in columns.
	- celsius_to_kelvin(temp_C), kelvin_to_celsius(temp_K): given temperature in one unit returns it in the other.
	- saturated_water_pressure(temp_C): calculates saturated water pressure with Beck equation over water given temperature in degrees Celsius. Returns SWP in hPa.
	- integrated_air_mass(min_height, max_height, data): calculates air mass using ideal gas approximation for every available point. Integrates the air mass over 1 cm^2 between given minimum and maximum height assuming that the temperature and pressure between the measured points are constant. Returns air mass over 1 cm^2 in kg/cm^2.
	- integrated_vapor_mass(min_height, max_height, data): calculates air mass using ideal gas approximation for every available point. Integrates the water vapour mass over 1 cm^2 between given minimum and maximum height assuming that the temperature and pressure between the measured points are constant. Returns water vapour mass over 1 cm^2 in kg/cm^2.
	- percent(integrated_mass_vapor, integrated_mass_air): calculates what percentage of total air mass is water vapour mass. Returns the percentage of water vapour in the air in %.
	- precipitable_water(integrated_mass_vapor): calculates precpitable water from integrated water vapour. Precipitable water is defined as a height to which the water would stand in the same cross-section as used with column of integrated water vapour if it would condens entirely. Returns precipitable water in cm.
	- day_of_year(year, month, day): calculates day of year from given date. Returns the day of year as int.
	- calculate_period(year1, month1, day1, year2, month2, day2, file_names, min_height, max_height, MET_site_name): decomposes calculating the whole period into calculating it month-by-month. Merges the results into one dataframe and applies the specific dates chosen by the user including days (download and calculations are always done on full months even if user wishes to plot one day only because of the way the files are stored in MET database, it's not the most optimal option but calculating one month takes well below 2 minutes). Saves the calculated data as .csv and returns the data as a dataframe.
	- calculate_one_month(min_height, max_height, file_name, MET_site_name): calculates saturated water pressure, integrated air mass and water vapour mass for the whole month. Returns the datafrme with the results for one launch.
	- plot_period(year1, month1, day1, year2, month2, day2, min_height, max_height, MET_site_name): plots the precipitable water vs. day of year and saves the plot as .png. Returns Void.
	- run(year1, month1, day1, year2, month2, day2, min_height, max_height, MET_site_name): check if the given dates are correct and automatically either picks up the data from the calculated file, recalculates the new period from already downloaded files or downloads the files from MET database depending on what is available. Returns dataframe with the results.
-------------------------------------------
-------------------------------------------

-------------------------------------------
---Compare.py------------------------------
The script allows to automatically download, unpack and plot data from the CIMEL photometer and radiosondes from given MET(radiosonde) and AEROnet(CIMEL) stations. It calculates and plots Precipitable Water (cm) vs. day of the year. Those plots use daily averages calculated from all available data for given day.

Coincident data plot plots daily averages only for days when both CIMEL and radiosonde data was available. Histogram of differences is calculated for this coincident data.

Script works only with scripts "Radiosonde.py" and "CIMEL.py" where function definitions can be found.
--Functions list--
	- plot_all(data_CIMEL, data_Radiosonde, year1, month1, day1, year2, month2, day2, launch_place): plots all data for given period. It doesn't check if both CIMEL and radiosonde data was available. Saves the plot as a .png and the data for plotting as .csv, the data is saved separately for CIMEL and radiosonde. Returns Void.
	- plot_coincident(data, year1, month1, day1, year2, month2, day2, launch_place): plots the data only for those days when both CIMEL and radiosonde measurement were available. CIMEL data is a daily average form all the measurements during the day, and radiosonde data is a mean from all the launches during the day (usually one around 11 am and one around 11 pm). Saves the plot as a .png and the data for plotting as .csv. Returns Void.
	- plot_histogram(data, year1, month1, day1, year2, month2, day2, launch_place): calculates the difference between the CIMEL and radiosonde measurements. For better comparison the difference is divided by the sum of PW from CIMEL and radiosonde to get the difference relative to the true value of the measurement. The difference is calculated and visualized as a histogram only for the coincident data. Saves the histogram as a .png and the data for plotting as .csv. Returns Void.
	- compare_latest(year1, month1, day1, min_height, max_height, MET_site_name, AEROnet_site_name, daily_averages): given the beginning date it downloades, calculates, compares and plots automatically the data from both CIMEL photometer and radiosonde from the given date to the latest available data (usually one day back). Returns the data as dataframe.
	- compare_period(year1, month1, day1, year2, month2, day2,
                   min_height, max_height,
                   MET_site_name, AEROnet_site_name, daily_averages):
-------------------------------------------
-------------------------------------------
---Data policy-----------------------------
The data downloaded by the script belongs respectively to the AEROnet network (CIMEL data) and Norwegian Meteorological Institute (radiosonde data) and any use, publication and privacy policies should be followed as stated on the websites of the databases.

Bugs, comments and questions about the scripts can be sent to: joanna.szulc.pl@gmail.com