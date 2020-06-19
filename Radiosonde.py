# -*- coding: utf-8 -*-
"""
Created on Mon Mar 30 12:35:54 2020

Download radiosonde data automatically from given MET station
(https://thredds.met.no/thredds/catalog/remotesensingradiosonde/catalog.html)
for given period, unpack to pandas dataFrameworks.
Calculate integrated water vapor (IWV) in kg/cm^2 and precipitable water (PW)
in cm, plot it against day of the year.

Compare with CIMEL data and plot through 'Compare.py'

joanna.szulc.pl@gmail.com
"""
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from netCDF4 import Dataset
import datetime
from tabulate import tabulate
import requests
import os

# Create target directories if they don't exist
def create_dir_year(year1, year2):
    year1 = int(year1)
    year2 = int(year2)
    diff = abs(year2 - year1)
    for i in range(diff + 1):
        year = year1 + i
        dirData = f'./data/{year}'
        if not os.path.exists(f'./data/{year}'):
            os.mkdir(dirData)


class InvalidDateError(ValueError):
    pass


def leap_year(year):
    if (year % 4) == 0:
        if (year % 100) == 0:
            if (year % 400) == 0:
                is_leap = True
            else:
                is_leap = False
        else:
            is_leap = True
    else:
        is_leap = False
    return is_leap


# Check if the date is correct
def is_date(year, month, day):
    year = int(year)
    month = int(month)
    day = int(day)
    thirty = [4, 6, 9, 11]
    thirty_one = [1, 3, 5, 7, 8, 10, 12]
    now = datetime.datetime.now()
    if year > now.year:
        raise InvalidDateError("No data yet")
        return False
    elif year < 1994:
        raise InvalidDateError("No archive data before 1994")
        return False
    elif month > 12:
        return False
    elif month < 1:
        return False
    elif day < 1:
        return False
    elif month == 2:
        if day < 1:
            return False
        if leap_year(year):
            if day > 29:
                return False
        else:
            if day > 28:
                return False
    elif month in thirty_one and day > 31:
        return False
    elif month in thirty and day > 30:
        return False
    elif year == now.year:
        if month > now.month:
            raise InvalidDateError("No data yet")
            return False
        if month == now.month:
            if day > now.day:
                raise InvalidDateError("No data yet")
                return False
    return True;


def check_beginning_end(year1, month1, day1, year2, month2, day2):
    date1 = is_date(year1, month1, day1)
    date2 = is_date(year2, month2, day2)
    year1 = int(year1)
    year2 = int(year2)
    month1 = int(month1)
    month2 = int(month2)
    day1 = int(day1)
    day2 = int(day2)
    if year1 > year2:
        raise InvalidDateError("Input has to be string in format (yyyy, mm, dd, yyyy, mm, dd, True/False, True/False) \nyyyy: 1994-2019, mm: 01-12, dd: 01-31")
        return False
    if year1 == year2:
        if month1 > month2:
            raise InvalidDateError("Input has to be string in format (yyyy, mm, dd, yyyy, mm, dd, True/False, True/False) \nyyyy: 1994-2019, mm: 01-12, dd: 01-31")
            return False
        if month1 == month2:
            if day1 > day2:
                raise InvalidDateError("Input has to be string in format (yyyy, mm, dd, yyyy, mm, dd, True/False, True/False) \nyyyy: 1994-2019, mm: 01-12, dd: 01-31")
                return False
            elif day1 == day2:
                print('You do realise you try to plot one day only?')
                return True
    if not date1:
        raise InvalidDateError("Input has to be string in format (yyyy, mm, dd, yyyy, mm, dd, True/False, True/False) \nyyyy: 1994-2019, mm: 01-12, dd: 01-31")
        return False
    if not date2:
        raise InvalidDateError("Input has to be string in format (yyyy, mm, dd, yyyy, mm, dd, True/False, True/False) \nyyyy: 1994-2019, mm: 01-12, dd: 01-31")
        return False
    return True


def download_period(year1, month1, year2, month2, download, MET_site_name):
    year1 = int(year1)
    year2 = int(year2)
    month1 = int(month1)
    month2 = int(month2)
    file_names = []
    if year1 == year2:
        file_names.append(download_one_year(year1, month1, month2, download, MET_site_name))
    elif year2 > year1:
        diff = abs(year2 - year1)
        for i in range(diff + 1):
            if i == 0:
                file_names.append(download_one_year(year1, month1, 12, download, MET_site_name))
            elif i == (diff):
                file_names.append(download_one_year(year2, 1, month2, download, MET_site_name))
            else:
                file_names.append(download_one_year(year1 + i, 1, 12, download, MET_site_name))
    return file_names


def get_period(year, month):
    months = ['01', '02', '03', '04', '05', '06', '07', '08', '09', '10', '11',
          '12']
    previous_month = months[month - 2]
    month = months[month - 1]
    # -2 not -1 becuase index from 0 and the data is saved from the last day
    # of the previous month in MET database
    
    thirty = ['04', '06', '09', '11']
    thirty_one = ['01', '03', '05', '07', '08', '10', '12']
    
    if previous_month in thirty_one:
        if previous_month == '12':
            previous_year = year - 1
            period_1 = f'{previous_year}1231'
        else:
            period_1 = f'{year}{previous_month}31'
    elif previous_month in thirty:
        period_1 = f'{year}{previous_month}30'
    elif previous_month == '02':
        if leap_year(year):
            period_1 = f'{year}{previous_month}29'
        else:
            period_1 = f'{year}{previous_month}28'
    
    if month in thirty_one:
        period_2 = f'-{year}{month}31'
    elif month in thirty:
        period_2 = f'-{year}{month}30'
    elif month == '02':
        if leap_year(year):
            period_2 = f'-{year}{month}29'
        else:
            period_2 = f'-{year}{month}28'
    
    period = period_1 + period_2
    return period


def download_one_year(year, month1, month2, download, MET_site_name):
        year = int(year)
        month1 = int(month1)
        month2 = int(month2)
        file_names = []
        
        diff = abs(month2 - month1)
        for i in range(diff + 1):
            period = get_period(year, month1 + i)
            file_name = f'./data/Radiosonde/{year}/{MET_site_name}_' + period + '.nc'
            core = "https://thredds.met.no/thredds/fileServer/remotesensingradiosonde"
            if (month1 + i) < 10:
                file_url = core + f'/{year}/0{month1 + i}/{MET_site_name}_' + period + '.nc'
            else:
                file_url = core + f'/{year}/{month1 + i}/{MET_site_name}_' + period + '.nc'
            if download:
                download_one_month(file_url, file_name)
                file_names.append(file_name)
            else:
                file_names.append(file_name)
        return file_names


def download_one_month(file_url, file_name):
    print(file_url)
    r = requests.get(file_url, stream=True)
    with open(file_name, "wb") as nc:
        for chunk in r.iter_content(chunk_size=1024):
            if chunk:
                nc.write(chunk)


def get_entries(fh):
    entries = len(fh.dimensions['time'])
    return entries
    

def prepare_data(fh, day, MET_site_name):
    height = fh.variables['geopotential_height'][day]
    pressure = fh.variables['air_pressure'][day]
    temperature = fh.variables['air_temperature'][day]
    relative_humidity = fh.variables['relative_humidity'][day]
    dew_point = fh.variables['dew_point_temperature'][day]

    height_units = fh.variables['geopotential_height'].units
    pressure_units = fh.variables['air_pressure'].units
    temperature_units = fh.variables['air_temperature'].units
    relative_humidity_units = fh.variables['relative_humidity'].units
    dew_point_units = fh.variables['dew_point_temperature'].units

    raw_data = pd.DataFrame()
    h = 'height [' + height_units + ']'
    p = 'pressure [' + pressure_units + ']'
    t = 'temperature [' + temperature_units + ']'
    r = 'relative_humidity [' + relative_humidity_units + ']'
    d = 'dew_point [' + dew_point_units + ']'
    raw_data.loc[:, h] = height
    raw_data.loc[:, p] = pressure
    raw_data.loc[:, t] = temperature
    raw_data.loc[:, r] = relative_humidity
    raw_data.loc[:, d] = dew_point
    
    
    time_of_launch = fh.variables['time'][day]
    launch_date = datetime.datetime.utcfromtimestamp(time_of_launch).strftime('%Y-%m-%d %H:%M')
    launch_date_day = datetime.datetime.utcfromtimestamp(time_of_launch).strftime('%d')
    place = f'\n{MET_site_name}: '
    place.capitalize()
    long = "%.f" % fh.variables['longitude'][0][0]
    lat = "%.f" % fh.variables['latitude'][0][0]
    launch_place = place + lat + '$^\circ$N ' + long + '$^\circ$E\n'

    # prepare the data - get rid of -9999 and -9.99
    masked_data = raw_data.mask(raw_data == (-999, -9.99, -999,
                                                     -999, -999))
    data = masked_data.dropna(axis=0, how='any')
    return data, launch_date, launch_date_day, launch_place


def celsius_to_kelvin(temp_C):

    kelvin = 273.15
    temp_K = temp_C + kelvin
    return temp_K


def kelvin_to_celsius(temp_K):

    kelvin = 273.15
    temp_C = temp_K - kelvin
    return temp_C


def saturated_water_pressure(temp_C):  # SWP with Beck equation over water in hPa

    saturated_water_pressure = 0.61115 * np.exp((18.678 - (temp_C / 234.5)) *
                                        (temp_C / (257.14 + temp_C)))  # kPa
    saturated_water_pressure = saturated_water_pressure * 10  # hPa
    return saturated_water_pressure

# Calculate approx. air mass from ideal gas equation
# data needs to be data_ANX from previous functions
def integrated_air_mass(min_height, max_height, data):

    data = data.mask(data.loc[:, 'height [m]'] > max_height)
    data = data.mask(data.loc[:, 'height [m]'] < min_height)
    data = data.dropna(axis=0, how='any')
    shape = data.shape

    R = 8.31446261815324  # J/mol*K, universal gas constant
    Mair = 0.0289628  # kg/mol, molecular mass of air
    window = []  # m
    n_air = []  # mol

    for i in range((shape[0] - 1)):
        if i == 0:
            window.append(abs(0 - data.iloc[i, 0]))
            V = 0.01 * 0.01 * window[i]  # m^3
            n_air.append((data.iloc[0, 10] * V) /
                         (R * data.iloc[0, 2]))
        else:
            window.append(abs(data.iloc[i, 0] -
                          data.iloc[i + 1, 0]))
            V = 0.01 * 0.01 * window[i]  # m^3
            n_air.append((data.iloc[i, 10] * V) /
                         (R * data.iloc[i, 2]))
    mass = pd.DataFrame()
    mass.loc[:, 'n_air [mol]'] = n_air
    mass.loc[:, 'mass_air [kg]'] = mass.loc[:, 'n_air [mol]'] * Mair
    integrated_air_mass = mass['mass_air [kg]'].sum()
    return integrated_air_mass


# Calculate approx. air mass from ideal gas equation and partial pressure of WV
# data needs to be data_ANX from previous functions
def integrated_vapor_mass(min_height, max_height, data): 

    data = data.mask(data.loc[:, 'height [m]'] > max_height)
    data = data.mask(data.loc[:, 'height [m]'] < min_height)
    data = data.dropna(axis=0, how='any')
    shape = data.shape

    R = 8.31446261815324  # J/mol*K, universal gas constant
    Mwv = 0.0180152833  # kg/mol, molecular mass of water vapour
    window = []  # m
    n_vapor = []  # mol

    for i in range((shape[0] - 1)):
        if i == 0:
            window.append(abs(0 - data.iloc[i, 0]))
            V = 0.01 * 0.01 * window[i]  # m^3
            n_vapor.append((data.iloc[0, 9] * V) /
                         (R * data.iloc[0, 2]))
        else:
            window.append(abs(data.iloc[i, 0] -
                          data.iloc[i + 1, 0]))
            V = 0.01 * 0.01 * window[i]  # m^3
            n_vapor.append((data.iloc[i, 9] * V) /
                         (R * data.iloc[i, 2]))
    mass = pd.DataFrame()
    mass.loc[:, 'n_vapor [mol]'] = n_vapor
    mass.loc[:, 'mass_vapor [kg]'] = mass.loc[:, 'n_vapor [mol]'] * Mwv
    integrated_vapor_mass = mass['mass_vapor [kg]'].sum()
    return integrated_vapor_mass


def percent(integrated_mass_vapor, integrated_mass_air):
    
    integrated_mass_vapor = np.array(integrated_mass_vapor)
    integrated_mass_air = np.array(integrated_mass_air)
    percent = (integrated_mass_vapor / integrated_mass_air) * 100
    return percent


def precipitable_water(integrated_mass_vapor):

    integrated_mass_vapor = np.array(integrated_mass_vapor)
    precipitable_water = integrated_mass_vapor * 1000
    return precipitable_water


def day_of_year(year, month, day):
    if month < 10:
        date_time_str = f'{year}-0{month}-{day}'
    else:
        date_time_str = f'{year}-{month}-{day}'
    date = datetime.datetime.strptime(date_time_str, '%Y-%m-%d')
    day = (date - datetime.datetime(date.year, 1, 1)).days + 1
    return int(day)


def calculate_period(year1, month1, day1, year2, month2, day2, file_names, min_height, max_height, MET_site_name):
    day = []
    data = pd.DataFrame()
    number_of_years = len(file_names)
    for i in range(number_of_years):
        number_of_files = len(file_names[i])
        for j in range(number_of_files):
            day.append(calculate_one_month(min_height, max_height, file_names[i][j], MET_site_name))
    
    data = pd.concat(day)
    save = f'./data/Radiosonde/{year1}/{MET_site_name}_{year1}{month1}{day1}-{year2}{month2}{day2}.csv'
    data.to_csv(save)
    
    data = pd.read_csv(f'./data/Radiosonde/{year1}/{MET_site_name}_{year1}{month1}{day1}-{year2}{month2}{day2}.csv')
    year1 = int(year1)
    month1 = int(month1)
    day1 = int(day1)
    year2 = int(year2)
    month2 = int(month2)
    day2 = int(day2)
    
    for i in data.index:
        if year1 == year2:
            first_day = day_of_year(year1, month1, day1)
            if int(data.loc[i, 'Day_of_Year']) < first_day:
                data.drop(i, inplace=True, axis=0)
        elif year1 != year2:
            if int(data.loc[i, 'year']) == year1:
                day = day_of_year(year1, month1, day1)
                if int(data.loc[i, 'Day_of_Year']) < day:
                    data.drop(i, inplace=True, axis=0)

    for j in data.index:
        if year1 == year2:
            last_day = day_of_year(year2, month2, day2)
            if int(data.loc[j, 'Day_of_Year']) > last_day:
                data.drop(j, inplace=True, axis=0)
        elif year1 != year2:
            if int(data.loc[j, 'year']) == year2:
                day = day_of_year(year2, month2, day2)
                if int(data.loc[j, 'Day_of_Year']) > day:
                    data.drop(j, inplace=True, axis=0)
                    
    save = f'./data/Radiosonde/{year1}/{MET_site_name}_{year1}{month1}{day1}-{year2}{month2}{day2}.csv'
    data.to_csv(save)
    return data


def calculate_one_month(min_height, max_height, file_name, MET_site_name):
    dataset = Dataset(file_name, mode='r')  # r - read only
    day = pd.DataFrame()
    number_of_entries = get_entries(dataset)
    percent_vapor = []
    pw = []
    integrated_mass_vapor = []
    integrated_mass_air = []
    launch_date = []
    launch_place = []
    launch_year = []
    for i in range(number_of_entries):
        data = prepare_data(dataset, i, MET_site_name)
        data_ANX = data[0]
        date = data[1]
        launch_date.append(data[1])
        launch_year.append(date[0:4])
        launch_place.append(data[3])

        # change units etc
        data_ANX.loc[:, "temperature [C]"] = kelvin_to_celsius(data_ANX.loc[:, "temperature [K]"])
        data_ANX.loc[:, "dew_point [C]"] = kelvin_to_celsius(data_ANX.loc[:, "dew_point [K]"])

        # calculate saturated water pressure
        data_ANX.loc[:, "SWP [hPa]"] = saturated_water_pressure(data_ANX.loc[:, 'temperature [C]'])

        # calculate partial pressure (PP)
        data_ANX.loc[:, "partial_pressure [hPa]"] = saturated_water_pressure(data_ANX.loc[:, 'dew_point [C]'])
        data_ANX.loc[:, "partial_pressure [Pa]"] = data_ANX.loc[:, "partial_pressure [hPa]"] * 100
        data_ANX.loc[:, "pressure [Pa]"] = data_ANX.loc[:, "pressure [hPa]"] * 100

        # calculating mass of water vapour up to 20 km
        integrated_mass_air.append(integrated_air_mass(min_height, max_height,
                                                       data_ANX))
        integrated_mass_vapor.append(integrated_vapor_mass(min_height,
                                                           max_height, data_ANX))
            
    percent_vapor = percent(integrated_mass_vapor, integrated_mass_air)
    pw = precipitable_water(integrated_mass_vapor)
    day.loc[:, 'integrated_mass_air [kg/cm^2]'] = integrated_mass_air
    day.loc[:, 'integrated_mass_vapor [kg/cm^2]'] = integrated_mass_vapor
    day.loc[:, 'percent_vapor [%]'] = percent_vapor
    day.loc[:, 'precipitable_water [cm]'] = pw
    day.loc[:, 'launch_date'] = launch_date
    day.loc[:, 'launch_place'] = launch_place
    day.loc[:, 'launch_date'] = pd.to_datetime(day.loc[:, 'launch_date'],
                                               format='%Y-%m-%d %H:%M')
    day.loc[:, 'Day_of_Year'] = day.loc[:, 'launch_date'].dt.dayofyear
    day.loc[:, 'year'] = launch_year
    dataset.close()
    return day


def plot_period(year1, month1, day1, year2, month2, day2, min_height, max_height, MET_site_name):
    data = run(year1, month1, day1, year2, month2, day2, min_height, max_height, MET_site_name)
    file_name = f'./data/Radiosonde/{year1}/{MET_site_name}_{year1}{month1}{day1}-{year2}{month2}{day2}.csv'
    data.dropna(inplace=True)
    
    fig, ax1 = plt.subplots(nrows=1, ncols=1, figsize=(14, 9))
    data.plot(kind='line', x='Day_of_Year', y='precipitable_water [cm]',
                        color='navy', ax=ax1, legend=False)
    ax1.grid(b=True)
    ax1.legend(loc='upper right')
    mylabel1 = ['Radiosonde']
    ax1.legend(labels=mylabel1)
    ax1.set_xlabel('Day of Year')
    ax1.set_ylabel('Precipitable Water [cm]')
    plt.ylim(bottom=0.0)
    
    ind = data.first_valid_index()
    site_name = data.loc[ind, 'launch_place']
    period = f'{year1}.{month1}-{year2}.{month2}'
    title = 'Precipitable Water from radiosonde soundings\n' + site_name + '\n'
    title = title + period
    fig.suptitle(title, fontsize=12)
    plt.subplots_adjust(top=0.87)
    plt.show()
    file_name = file_name.replace('.csv', '.png')
    file_name = file_name.replace('./data/', './plots/')
    plt.savefig(file_name, bbox_inches='tight')


def run(year1, month1, day1, year2, month2, day2, min_height, max_height, MET_site_name):
    if check_beginning_end(year1, month1, day1, year2, month2, day2):
        #  try to open calculated data
        try:
            data = pd.read_csv(f'./data/Radiosonde/{year1}/{MET_site_name}_{year1}{month1}{day1}-{year2}{month2}{day2}.csv')
            print("Radiosonde: Data succesfully loaded from file")
            return data
        #  if data isn't calculated yet
        except FileNotFoundError:
            #  try to caulculate data from already downloaded METdata
            try:
                print("Radiosonde: Data will be calculated from raw data. It may take some time.")
                file_names = download_period(year1, month1, year2, month2, False, MET_site_name)
                data = calculate_period(year1, month1, day1, year2, month2, day2, file_names, min_height, max_height, MET_site_name)
                return data
            #  if it fails download the files from MET
            except FileNotFoundError:
                print("Radiosonde: Data will be downloaded from MET database and calculated. It may take some time.")
                create_dir_year(year1, year2)
                file_names = download_period(year1, month1, year2, month2, True, MET_site_name)
                data = calculate_period(year1, month1, day1, year2, month2, day2, file_names, min_height, max_height, MET_site_name)
                return data


MET_site_name = 'andoya'
run('2017', '08', '24', '2017', '08', '24', 0, 50000, MET_site_name)