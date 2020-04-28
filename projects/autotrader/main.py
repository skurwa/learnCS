from alpha_vantage.timeseries import TimeSeries
# Your key here
key = 'CYU9H6PTEBDEJS2Z'
ts = TimeSeries(key)
aapl, meta = ts.get_daily(symbol='AAPL')
print(aapl['2020-04-21'])
