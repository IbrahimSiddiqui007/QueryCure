# QueryCure
This project is a C++ application that integrates with an Oracle database using the sqlAPI++ library. It includes a graphical user interface built using the wxWidgets library.

## Project Scope & Objectives  

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
 
### Microsoft Visual Studio Community Edition
Used as the IDE and debugger for the project.

### C++ 
Used for the logic implementation and connection to SQL databases. 

### wxWidgets (C++ GUI) 
Used as a C++ library to implement a graphical interface.

### sqlAPI++ 
C++ library that allows PL/SQL statements to be run from C++ functions. 

### Oracle Express Edition 21c Database and Oracle Instant Client
Used to test the application and interact with Oracle databases.

### Windows 10/11 
Used to develop and test the application. 

## Installation 
To install this project, clone the repository to your local machine and open this repo using Visual Studio.
Also, add SQLAPI++ to a properties project

## Suggestions
Here are some suggestions to consider when working with this software stack:
- [X] Consider using a version control system like Git to manage your codebase and collaborate with others.
- [ ] Be aware of the security risks associated with interacting with databases and take appropriate measures to protect sensitive data.
- [ ] Use automated testing frameworks and unit testing to ensure that the application is robust and reliable.
- [ ] Keep in mind the end-users of the application and ensure that the GUI design and user experience are intuitive and user-friendly.


## Known Issues
- None

## Contributing
To contribute to this project, please submit any issues or pull requests on the GitHub repository.

## License
This project is licensed under the GPL-3.0 license. See the LICENSE file for details.
