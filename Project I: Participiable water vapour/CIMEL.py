# -*- coding: utf-8 -*-
"""
Created on Tue Mar 31 15:01:14 2020

Download CIMEL photometer data automatically from given AEROnet site
(https://aeronet.gsfc.nasa.gov/cgi-bin/webtool_aod_v3?stage=3&region=Europe&
state=Norway&site=Andenes&place_code=10)
for given period, unpack to pandas dataFrameworks.
Plot precipitable water (PW) in cm.

Compare with CIMEL data and plot through 'Compare.py'

joanna.szulc.pl@gmail.com
"""

import pandas as pd
import matplotlib.pyplot as plt
import requests
import datetime
import os


# Create target directories if they don't exist
def create_dir_year(year1, year2):
    year1 = int(year1)
    year2 = int(year2)
    diff = abs(year2 - year1)
    for i in range(diff + 1):
        year = year1 + i
        dirData = f'./data/CIMEL/{year}'
        if not os.path.exists(f'./data/CIMEL/{year}'):
            os.mkdir(dirData)


class InvalidDateError(ValueError):
    pass


def leap_year(year):
    year = int(year)
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
    elif year < 2009:
        raise InvalidDateError("No archive data older than 2009")
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
    return True


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
        raise InvalidDateError("Input has to be string in format (yyyy, mm, dd, yyyy, mm, dd, True/False, True/False) \nyyyy: 2009-2019, mm: 01-12, dd: 01-31")
        return False
    if year1 == year2:
        if month1 > month2:
            raise InvalidDateError("Input has to be string in format (yyyy, mm, dd, yyyy, mm, dd, True/False, True/False) \nyyyy: 2009-2019, mm: 01-12, dd: 01-31")
            return False
        if month1 == month2:
            if day1 > day2:
                raise InvalidDateError("Input has to be string in format (yyyy, mm, dd, yyyy, mm, dd, True/False, True/False) \nyyyy: 2009-2019, mm: 01-12, dd: 01-31")
                return False
            elif day1 == day2:
                print('You do realise you try to plot one day only?')
                return True
    if not date1:
        raise InvalidDateError("Input has to be string in format (yyyy, mm, dd, yyyy, mm, dd, True/False, True/False) \nyyyy: 2009-2019, mm: 01-12, dd: 01-31")
        return False
    if not date2:
        raise InvalidDateError("Input has to be string in format (yyyy, mm, dd, yyyy, mm, dd, True/False, True/False) \nyyyy: 2009-2019, mm: 01-12, dd: 01-31")
        return False
    return True


# download automatically for period in format, (yyyy, mm, dd, yyyy, mm, dd)
# save to file, returns file_name for reading the file, download - boolean
# True - download, False - just return the filename for the period,
# daily averages - boolean, True - daily averages, False - all points
def download_data(year1, month1, day1, year2, month2, day2, AEROnet_site_name,
                  download, daily_averages_b):
    if check_beginning_end(year1, month1, day1, year2, month2, day2):
        core = 'https://aeronet.gsfc.nasa.gov/cgi-bin/print_web_data_v3?'
        site = f'site={AEROnet_site_name}&'
        year_begin = f'year={year1}&'
        month_begin = f'month={month1}&'
        day_begin = f'day={day1}&'
        year_stop = f'year2={year2}&'
        month_stop = f'month2={month2}&'
        day_stop = f'day2={day2}&'
        quality_level = 'AOD10=1&'
        daily_averages = 'AVG=20'
        all_points = 'AVG=10'
        if download:
            if daily_averages_b:
                file_url = core + site + year_begin + month_begin + day_begin \
                + year_stop + month_stop + day_stop + quality_level \
                + daily_averages
                file_name = f'./data/CIMEL/{year1}/CIMEL_' + AEROnet_site_name\
                + f'_{year1}' + f'{month1}' + f'{day1}' + '_' + f'{year2}'\
                + f'{month2}' + f'{day2}' + '_daily_averages' + '.lev10'
            elif not daily_averages_b:
                file_url = core + site + year_begin + month_begin + day_begin\
                + year_stop + month_stop + day_stop + quality_level\
                + all_points
                file_name = f'./data/CIMEL/{year1}/CIMEL_' + AEROnet_site_name\
                + f'_{year1}' + f'{month1}' + f'{day1}' + '_' + f'{year2}'\
                + f'{month2}' + f'{day2}' + '_all_points' + '.lev10'
            r = requests.get(file_url, stream=True)
            with open(file_name, "wb") as lev10:
                for chunk in r.iter_content(chunk_size=1024):
                    if chunk:
                        lev10.write(chunk)
        else:
            if daily_averages_b:
                file_name = f'./data/CIMEL/{year1}/CIMEL_' + AEROnet_site_name\
                + f'_{year1}' + f'{month1}' + f'{day1}' + '_' + f'{year2}'\
                + f'{month2}' + f'{day2}' + '_daily_averages' + '.lev10'
            elif not daily_averages_b:
                file_name = f'./data/CIMEL/{year1}/CIMEL_' + AEROnet_site_name\
                + f'_{year1}' + f'{month1}' + f'{day1}' + '_' + f'{year2}'\
                + f'{month2}' + f'{day2}' + '_all_points' + '.lev10'
        return file_name

# file should be .lev10 AEROnet file
def read_from_file(file_name):
    raw_data = pd.read_csv(file_name, skiprows=7,
                           parse_dates=[['Date(dd:mm:yyyy)', 'Time(hh:mm:ss)']])
    raw_data.drop(raw_data.tail(1).index, inplace=True) #  droping last line, because it's just html
    unmasked_data = pd.DataFrame(raw_data.loc[:, ['Date(dd:mm:yyyy)_Time(hh:mm:ss)',
                                     'Day_of_Year',
                                     'Precipitable_Water(cm)',
                                     'AERONET_Instrument_Number',
                                     'AERONET_Site_Name',
                                     'Site_Latitude(Degrees)',
                                     'Site_Longitude(Degrees)']])

    masked_data = pd.DataFrame(unmasked_data.mask(unmasked_data == (-999, -999,
                                                                    -999, -999,
                                                                    -999, -999,
                                                                    -999)))
    
    data = pd.DataFrame(masked_data.dropna(axis=0, how='any'))
    data.loc[:, 'Date'] = pd.to_datetime(data.loc[:,
                                            'Date(dd:mm:yyyy)_Time(hh:mm:ss)'],
                                            format='%d:%m:%Y %H:%M:%S')
    return data


def run_CIMEL(year1, month1, day1, year2, month2, day2, AEROnet_site_name,
              daily_averages):
    try:
        download = False
        file_name = download_data(year1, month1, day1, year2, month2, day2,
                                  AEROnet_site_name, download, daily_averages)
        data = read_from_file(file_name)
        print('CIMEL: Succesfully read from file')
        return data
    
    except FileNotFoundError:
        download = True
        print('CIMEL: Downloading from AEROnet database')
        create_dir_year(year1, year2)
        file_name = download_data(year1, month1, day1, year2, month2, day2,
                                  AEROnet_site_name, download, daily_averages)
        data = read_from_file(file_name)
        return data


def plot_CIMEL(year1, month1, day1, year2, month2, day2, AEROnet_site_name,
               daily_averages):
    data = run_CIMEL(year1, month1, day1, year2, month2, day2,
                     AEROnet_site_name, daily_averages)
    file_name = download_data(year1, month1, day1, year2, month2, day2,
                              AEROnet_site_name, False, daily_averages)
    fig, ax1 = plt.subplots(nrows=1, ncols=1, figsize=(14, 9))
    data.plot(kind='line', x='Day_of_Year', y='Precipitable_Water(cm)',
              color='navy', ax=ax1, legend=False)
    ax1.grid(b=True)
    ax1.legend(loc='upper right')
    mylabel1 = ['CIMEL']
    ax1.legend(labels=mylabel1)
    ax1.set_xlabel('Day of Year')
    ax1.set_ylabel('Precipitable Water [cm]')
    plt.ylim(bottom=0.0)
    
    ind = data.first_valid_index()
    long = data.loc[ind, 'Site_Longitude(Degrees)']
    lat = data.loc[ind, 'Site_Latitude(Degrees)']
    long = "%.2f" % long
    lat = "%.2f" % lat
    long = str(long)
    lat = str(lat)
    site_name = AEROnet_site_name
    period = file_name[32:49]
    period = period.replace('_', '-')
    period = period[0:4] + '.' + period[4:6] + '.' + period[6:13] + '.'\
             + period[13:15] + '.' + period[15:17]
    is_daily_average = file_name[50:64]
    if is_daily_average == 'daily_averages':
        is_daily_average = 'Daily averages'
    else:
        is_daily_average == 'All points'
    title = 'Precipitable Water from CIMEL measurements\n' + site_name\
            + ', ' + lat + '$^\circ$N ' + long + '$^\circ$E\n'
    title = title + period + '\n' + is_daily_average
    fig.suptitle(title, fontsize=12)
    plt.subplots_adjust(top=0.87)
    plt.show()
    save = file_name.replace('./data/', './plots/')
    save = save.replace('.lev10', '.png')
    plt.savefig(save, bbox_inches='tight')

    save = save.replace('.png', '.csv')
    data.to_csv(save)
