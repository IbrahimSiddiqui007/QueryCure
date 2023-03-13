# QueryCure

## Project scope and Objectives  

Query Cure is a database diagnosis tool which is made using C++. It can be installed on any client/server where the diagnosis is run. The tool will gain insights based on the database and display suggestions on how to improve the performance such as denormalization, indexing, clustering, etc. It involves the following components: 

### Data Collection 

It can collect performance metrics and data from the Oracle database server. This data can include information on CPU utilization, memory usage, disk I/O, and other database-related statistics. 

### Data Analysis 

It can analyze the data collected and identify any performance issues or bottlenecks in the database. This can involve identifying slow-running queries, inefficient indexing, or other performance-related issues. 

### Recommendations 

Once the tool has identified performance issues, it should provide recommendations for improving the performance of the database. This can include suggestions for tuning the database configuration, optimizing SQL queries, or adding or modifying database indexes. 

### Reporting 

The tool should be able to generate reports that summarize the performance of the database, including any issues that were identified and any recommendations for improvement. 

### Monitoring 

It monitors the performance of the database over time and provides alerts if performance issues occur. This can include monitoring the database for spikes in resource utilization or other anomalies that could indicate a performance problem. 

## Methodology and Technology used  
 
### Microsoft Visual Studio 
Used as the IDE and debugger. 

### C++ 
Logic implementation and connection to SQL databases. 

### wxWidgets (C++ GUI) 
C++ library is used to implement a graphical interface. 

### sqlAPI++ 
C++ library that allows PL/SQL statements to be run from C++ functions. 

### Oracle Database 
The database was used to test the application. 

### Windows 10/11 
Used to develop and test the application. 
