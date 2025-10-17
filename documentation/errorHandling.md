# Error handling guide

## About Tracelog

### Basic Usage
The raylib function for logging is called Tracelog().  
It takes 2 arguments: LOG_LEVEL and error description.  
Example:
```
Tracelog(LOG_ERROR, "there was and error")
```
It can also take additional arguments to be used in the string like an fString.  
Example:
```
Traclog(LOG_INFO, "Player pos: %f,%f", pos.x, pos.y)
```

### Available log levels
The available log levels in raylib are:
- LOG_ALL: Enables all log levels, providing the most detailed output.
- LOG_TRACE: Detailed trace information, useful for tracking execution flow.
- LOG_DEBUG: Debugging information, often used during development.
- LOG_INFO: Informational messages about the application's state or actions.
- LOG_WARNING: Warnings about potential issues or non-critical errors.
- LOG_ERROR: Error conditions that may affect the application's functionality.
- LOG_FATAL: Critical errors that cause the application to terminate.
- LOG_NONE: Disables all logging output. 

You can set the desired log level using the SetTraceLogLevel() function.  
Example:
```
SetTraceLogLevel(LOG_FATAL);
```

## Our usage
Unless specified in the following section all logging should use your best judgment on when to use it and at what level. In general if an action can fail it should probably be logged.  

Items in the following sections should always be logged

### Asset Loading
All asset loading should log failures at the LOG_ERROR level

### Major Game State Changes
Any large change to the game state such as:  
- Adding an entity
- Destroying an entity
Should log at the LOG_INFO level
