# -*- coding: utf-8 -*-
"""
Created on Tue Mar 31 20:48:54 2020

The script allows to automatically download, unpack and plot data from
the CIMEL photometer and radiosondes from given MET(radiosonde) and 
AEROnet(CIMEL) stations. It calculates and plots Precipitable Water (cm) vs. 
day of the year. Those plots use daily averages calculated from all available
data for given day.

Coincident data plot plots daily averages only for days when both CIMEL and
radiosonde data was available. Histogram of differences is calculated for
this coincident data.

Script works only with scripts "Radiosonde.py" and "CIMEL.py" where function
definitions can be found.

Further information can be found in comments or "READ_ME.txt".

joanna.szulc.pl@gmail.com
"""

import pandas as pd
import matplotlib.pyplot as plt
import datetime
import Radiosonde as rs
import CIMEL as C


#  plots all available data for CIMEL and Radiosonde without any additional averaging
#  default is daily average for CIMEL downloaded from AEROnet and 2 launches
#  per day for radiosonde data
def plot_all(data_CIMEL, data_Radiosonde, year1, month1, day1, year2, month2, day2, launch_place):
    fig, ax1 = plt.subplots(nrows=1, ncols=1, figsize=(14, 9))
    ind = data_Radiosonde.first_valid_index()
    data_Radiosonde.drop(ind, axis=0, inplace=True)
    data_CIMEL.plot(kind='line', x='Day_of_Year', y='Precipitable_Water(cm)',
                       color='navy', ax=ax1, legend=False)
    data_Radiosonde.plot(kind='line', x='Day_of_Year', y='precipitable_water [cm]',
                        color='violet', ax=ax1, legend=False)
    ax1.set_ylabel("Precipitable water (cm)")
    ax1.grid(b=True)
    ax1.legend(loc='upper right')
    mylabel1 = ['CIMEL', 'Radiosonde']
    ax1.legend(labels=mylabel1)
    plt.ylim(bottom=0.0)
    plt.xlim(left=-5, right=370)
    
    long = data_CIMEL.loc[1, 'Site_Longitude(Degrees)']
    lat = data_CIMEL.loc[1, 'Site_Latitude(Degrees)']
    long = "%.2f" % long
    lat = "%.2f" % lat
    long = str(long)
    lat = str(lat)
    site_name = launch_place
    period = f'{year1}.{month1}.{day1}-{year2}.{month2}.{day2}'

    title = 'Precipitable Water measurements comparison\n'+ 'All available data on daily averages' + site_name + '\n'
    title = title + period + '\n'
    
    fig.suptitle(title, fontsize=12)
    plt.subplots_adjust(top=0.87)
    plt.show()
    save = f'./plots/Compare/{year1}/Andenes_{year1}{month1}{day1}-{year2}{month2}{day2}_all.png'
    plt.savefig(save, bbox_inches='tight')

    save = f'./plots/Compare/{year1}/Andenes_{year1}{month1}{day1}-{year2}{month2}{day2}_all_CIMEL.csv'
    data_CIMEL.to_csv(save)
    
    save = f'./plots/Compare/{year1}/Andenes_{year1}{month1}{day1}-{year2}{month2}{day2}_all_Radiosonde.csv'
    data_CIMEL.to_csv(save)
    
    
#  plots data only for days when both CIMEL and radiosonde was available
#  CIMEL is by default daily average from AEROnet data, radiosonde data is a 
#  mean calculated from the launches during the day (usually one 11 am, one 11 pm)
def plot_coincident(data, year1, month1, day1, year2, month2, day2, launch_place):
    fig, ax1 = plt.subplots(nrows=1, ncols=1, figsize=(14, 9))
    data.plot(kind='line', x='Day_of_Year', y='Precipitable_Water(cm)',
                       color='navy', ax=ax1, legend=False)
    data.plot(kind='line', x='Day_of_Year', y='precipitable_water [cm]',
                        color='violet', ax=ax1, legend=False)
    ax1.set_ylabel("Precipitable water (cm)")
    ax1.grid(b=True)
    ax1.legend(loc='upper right')
    mylabel1 = ['CIMEL', 'Radiosonde']
    ax1.legend(labels=mylabel1)
    plt.ylim(bottom=0.0)
    
    ind = data.first_valid_index()
    long = data.loc[ind, 'Site_Longitude(Degrees)']
    lat = data.loc[ind, 'Site_Latitude(Degrees)']
    long = "%.2f" % long
    lat = "%.2f" % lat
    long = str(long)
    lat = str(lat)
    site_name = launch_place
    period = f'{year1}.{month1}.{day1}-{year2}.{month2}.{day2}'

    title = 'Precipitable Water measurements comparison\n' + 'Daily averages for coincident data' + site_name + '\n'
    title = title + period + '\n'
    
    fig.suptitle(title, fontsize=12)
    plt.subplots_adjust(top=0.87)
    plt.show()
    save = f'./plots/Compare/{year1}/Andenes_{year1}{month1}{day1}-{year2}{month2}{day2}_coincident.png'
    plt.savefig(save, bbox_inches='tight')

    save = save.replace('.png', '.csv')
    data.to_csv(save)


#  plot histogram of differences for the same data as used in plot_coincident
#  defualt is daily average for CIMEL, and mean value from 2 launches for
#  radiosonde, only on days when both measurements were available
def plot_histogram(data, year1, month1, day1, year2, month2, day2, launch_place):
    data.loc[:, "Difference"] = (abs(data.loc[:, 'Precipitable_Water(cm)']
                                - data.loc[:, 'precipitable_water [cm]'])
                                / (data.loc[:, 'precipitable_water [cm]'] 
                                + data.loc[:, 'Precipitable_Water(cm)']))
    
    fig, ax1 = plt.subplots(nrows=1, ncols=1, figsize=(14, 9))
    
    data.hist(column="Difference", ax=ax1, bins=50)
    ax1.set_title(' ')
    ax1.set_ylabel("Number of entries")
    ax1.set_xlabel("$\Delta$PW [cm]")
    ax1.grid(b=True)
    ax1.legend(loc='upper right')
    mylabel1 = ['Comparison']
    ax1.legend(labels=mylabel1)
    plt.ylim(bottom=0.0)
    
    ind = data.first_valid_index()
    long = data.loc[ind, 'Site_Longitude(Degrees)']
    lat = data.loc[ind, 'Site_Latitude(Degrees)']
    long = "%.2f" % long
    lat = "%.2f" % lat
    long = str(long)
    lat = str(lat)
    site_name = launch_place
    period = f'{year1}.{month1}.{day1}-{year2}.{month2}.{day2}'

    title = 'Histogram of differences for coincident data'
    deltaPW = '$\Delta$PW = |$PW^{Radiosonde}$ - $PW^{CIMEL}$| / ($PW^{Radiosonde}$ + $PW^{CIMEL}$)'
    title = title + site_name + period + '\n' + deltaPW
    
    fig.suptitle(title, fontsize=12)
    plt.subplots_adjust(top=0.87)
    plt.show()
    save = f'./plots/Compare/{year1}/Andenes_{year1}{month1}{day1}-\
    {year2}{month2}{day2}_histogram.png'
    plt.savefig(save, bbox_inches='tight')

    save = save.replace('.png', '.csv')
    data.to_csv(save)


def compare_latest(year1, month1, day1, min_height, max_height, MET_site_name,
                   AEROnet_site_name, daily_averages):
    now = datetime.datetime.now()
    year2 = str(now.year)
    month2 = now.month
    if month2 < 10:
        month2 = str(month2)
        month2 = '0' + month2
    else:
        month2 = str(now.month)
        
    day2 = now.day
    if day2 < 10:
        day2 = str(day2)
        day2 = '0' + day2
    else:
        day2 = str(now.day)

    data_CIMEL = C.run_CIMEL(year1, month1, day1, year2, month2, day2,
                             AEROnet_site_name, daily_averages)
    
    data_Radiosonde = rs.run(year1, month1, day1, year2, month2, day2,
                             min_height, max_height, MET_site_name)
    ind = data_Radiosonde.first_valid_index()
    launch_place = data_Radiosonde.loc[ind, 'launch_place']
    plot_all(data_CIMEL, data_Radiosonde, year1, month1, day1,
             year2, month2, day2, launch_place)
   
    grouped_data_Radiosonde = data_Radiosonde.groupby('Day_of_Year')
    data_Radiosonde_mean = grouped_data_Radiosonde.mean()
   
    data = pd.DataFrame()
    data = pd.merge(data_CIMEL,
                    data_Radiosonde_mean,
                    left_on = 'Day_of_Year',
                    right_on = 'Day_of_Year',
                    how='left')
    data = data.dropna(axis=0, how='any')
    
    plot_coincident(data, year1, month1, day1, year2, month2, day2,
                    launch_place)
    plot_histogram(data, year1, month1, day1, year2, month2, day2,
                   launch_place)


def compare_period(year1, month1, day1, year2, month2, day2,
                   min_height, max_height,
                   MET_site_name, AEROnet_site_name, daily_averages):
    data_CIMEL = C.run_CIMEL(year1, month1, day1, year2, month2, day2,
                             AEROnet_site_name, daily_averages)
    
    data_Radiosonde = rs.run(year1, month1, day1, year2, month2, day2,
                             min_height, max_height, MET_site_name)
    ind = data_Radiosonde.first_valid_index()
    launch_place = data_Radiosonde.loc[ind, 'launch_place']
    plot_all(data_CIMEL, data_Radiosonde, year1, month1, day1,
             year2, month2, day2, launch_place)
    
    grouped_data_Radiosonde = data_Radiosonde.groupby('Day_of_Year')
    data_Radiosonde_mean = grouped_data_Radiosonde.mean()
    
    data = pd.DataFrame()
    data = pd.merge(data_CIMEL,
                    data_Radiosonde_mean,
                    left_on = 'Day_of_Year',
                    right_on = 'Day_of_Year',
                    how='left')
    data = data.dropna(axis=0, how='any')
    
    plot_coincident(data, year1, month1, day1, year2, month2, day2,
                    launch_place)
    plot_histogram(data, year1, month1, day1, year2, month2, day2,
                   launch_place)


year1 = '2019'
month1 = '02'
day1 = '15'
year2 = '2019'
month2 = '03'
day2 = '11'
AEROnet_site_name = 'Andenes'
MET_site_name = 'andoya'
min_height = 376
max_height = 20000
daily_averages = True

compare_period(year1, month1, day1, year2, month2, day2,
               min_height, max_height,
               MET_site_name, AEROnet_site_name, daily_averages)
