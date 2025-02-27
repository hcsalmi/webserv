# **webserv** <br>
<br>
The gist of it:<br>
This Hive Helsinki group project is about writing your own HTTP server modelled after NGINX. Not all RFC features are implemented, only the ones specified in the project requirements.<br>
<br>

**Requirements:**<br>
• Your program has to take a configuration file as argument, or use a default path.<br>
• You can’t execve another web server.<br>
• Your server must never block and the client can be bounced properly if necessary.<br>
• It must be non-blocking and use only 1 poll() (or equivalent) for all the I/O operations between the client and the server (listen included).<br>
• poll() (or equivalent) must check read and write at the same time.<br>
• You must never do a read or a write operation without going through poll() (or equivalent).<br>
• Checking the value of errno is strictly forbidden after a read or a write operation.<br>
• You don’t need to use poll() (or equivalent) before reading your configuration file.<br>
• You can use every macro and define like FD_SET, FD_CLR, FD_ISSET, FD_ZERO.<br>
• A request to your server should never hang forever.<br>
• Your server must be compatible with the web browser of your choice.<br>
• We will consider that NGINX is HTTP 1.1 compliant and may be used to compare headers and answer behaviors.<br>
• Your HTTP response status codes must be accurate.<br>
• You server must have default error pages if none are provided.<br>
• You can’t use fork for something else than CGI (like PHP, or Python, and so forth).<br>
• You must be able to serve a fully static website.<br>
• Clients must be able to upload files.<br>
• You need at least GET, POST, and DELETE methods.<br>
• Your server must stay available at all costs.<br>
• Your server must be able to listen to multiple ports.<br>
<br>

**In the configuration file, you should be able to:**<br>
• Choose the port and host of each ’server’.<br>
• Setup the server_names or not.<br>
• The first server for a host:port will be the default for this host:port (that means it will answer to all the requests that don’t belong to an other server).<br>
• Setup default error pages.<br>
• Limit client body size.<br>
• Setup routes with one or multiple of the following rules/configuration (routes wont be using regexp):<br>
&emsp;◦ Define a list of accepted HTTP methods for the route.<br>
&emsp;◦ Define a HTTP redirection.<br>
&emsp;◦ Define a directory or a file from where the file should be searched (for example, if url /kapouet is rooted to /tmp/www,<br>
&emsp; url /kapouet/pouic/toto/pouet is /tmp/www/pouic/toto/pouet).<br>
&emsp;◦ Turn on or off directory listing.<br>
&emsp;◦ Set a default file to answer if the request is a directory.<br>
&emsp;◦ Execute CGI based on certain file extension (for example .php).<br>
&emsp;◦ Make it work with POST and GET methods.<br>
&emsp;◦ Make the route able to accept uploaded files and configure where they should be saved.<br>
&emsp;&emsp;∗ Because you won’t call the CGI directly, use the full path as PATH_INFO.<br>
&emsp;&emsp;∗ For a chunked request, your server needs to unchunk it. The CGI will expect EOF as end of the body.<br>
&emsp;&emsp;∗ Same things for the output of the CGI. If no content_length is returned from the CGI, EOF will mark the end of the returned data.<br>
&emsp;&emsp;∗ Your program should call the CGI with the file requested as first argument.<br>
&emsp;&emsp;∗ The CGI should be run in the correct directory for relative path file access.<br>
&emsp;&emsp;∗ Your server should work with one CGI (php-CGI, Python, and so forth).<br>


