# Heading1**webserv** <br>
<br>
The gist of it:<br>
This Hive Helsinki group project is about writing your own HTTP server modelled after NGINX. Not all RFC features are implemented, only the ones specified in the project requirements.<br>
<br>

Requirements<br>
• Your program has to take a configuration file as argument, or use a default path.<br>
• You can’t execve another web server.<br>
• Your server must never block and the client can be bounced properly if necessary.<br>
• It must be non-blocking and use only 1 poll() (or equivalent) for all the I/O operations between the client and the server (listen included).<br>
• poll() (or equivalent) must check read and write at the same time.<br>
• You must never do a read or a write operation without going through poll() (or equivalent).<br>
• Checking the value of errno is strictly forbidden after a read or a write operation.<br>
• You don’t need to use poll() (or equivalent) before reading your configuration file.<br>
• You can use every macro and define like FD_SET, FD_CLR, FD_ISSET, FD_ZERO (understanding what and how they do it is very useful).<br>
• A request to your server should never hang forever.<br>
• Your server must be compatible with the web browser of your choice.<br>
• We will consider that NGINX is HTTP 1.1 compliant and may be used to compare headers and answer behaviors.<br>
• Your HTTP response status codes must be accurate.<br>
• You server must have default error pages if none are provided.<br>
• You can’t use fork for something else than CGI (like PHP, or Python, and so forth).<br>
• You must be able to serve a fully static website.<br>
• Clients must be able to upload files.<br>
• You need at least GET, POST, and DELETE methods.<br>
• Stress tests your server. It must stay available at all cost.<br>
• Your server must be able to listen to multiple ports (see Configuration file).<br>
