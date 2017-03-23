/* module: strings.c */

static char SccsId[] = "@(#)strings.c	1.38";

/* define message strings, no particular order besides numeric */

char* STRXXX = "Undefined Error String #@&*!";
char* STR001 = "Problem accessing digitizer";
char* STR002 = "Digitizer not at home position";
char* STR003 = "Digitizer data input error";
char* STR004 = "Problem controlling digitizer";
char* STR005 = "Problem accessing DNC link";
char* STR006 = "DNC link error";
char* STR007 = "Mill does not support QUILLUP command";
char* STR008 = "Memory problem, try switching off power and restarting";
char* STR009 = "Parameter data problem, cannot continue";
char* STR010 = "Command failed";
char* STR011 = "Unrecognized command";
char* STR012 = "Unimplemented command";
char* STR013 = "No current image";
char* STR014 = "Image must be filled first";
char* STR015 = "Warning: VOID longitude";
char* STR016 = "Number out of range";
char* STR017 = "Latitude range is too small";
char* STR018 = "Longitude range is too small";
char* STR019 = "Invalid latitude period";
char* STR020 = "Invalid longitude period";
char* STR021 = "Current image must be saved or cleared";
char* STR022 = "Cannot open file";
char* STR023 = "Digitizer sync error (missing)";
char* STR024 = "Digitizer sync error (misplaced)";
char* STR025 = "Image has VOID zone, check settings, retry";
char* STR026 = "Image file error on seek";
char* STR027 = "Image file error on read";
char* STR028 = "Image file error on write";
char* STR029 = "Tabulation of radii (mm/10) in longitude";
char* STR030 = "Raster refresh error PEBLKWR";
char* STR031 = "Window manager error";
char* STR032 = "Error accessing printer";
char* STR033 = "Warning: voids in image, command gives unexpected results";
char* STR034 = "Latitude or longitude range of one makes a null surface";
char* STR035 = "Image data exceeds tool Z range";
char* STR036 = "Tool diameter out of range";
char* STR037 = "Already clear";
char* STR038 = "UNNAMED";
char* STR039 = "Is Echo Startup Disc inserted?";
char* STR040 = "Cannot find or create file";
char* STR041 = "Is Echo Startup Disc inserted and writeable?";
char* STR042 = "Undefined option";
char* STR043 = "\nR Lookup Table:";
char* STR044 = "\nZ Lookup Table:";
char* STR045 = "Serial           ";
char* STR046 = "Data Format Type ";
char* STR047 = "Vertical Range   ";
char* STR048 = "Horizontal Range ";
char* STR049 = "Horizontal Offset";
char* STR050 = "Horizontal Center";
char* STR051 = "Gauge Height     ";
char* STR052 = "Gauge Width      ";
char* STR053 = "Basic Angle      ";
char* STR054 = "Samples per Frame";
char* STR055 = "Frames per Image ";
char* STR056 = "Radius Steps     ";
char* STR057 = "\nCorrection Lookup Table, samples across, frames down:\n";
char* STR058 = "You may want to make a new Correction Table";
char* STR059 = "Standby...Computing new geometry lookup tables";
char* STR060 = "Error occured while reading file";
char* STR061 = "Error occured while writing file";
char* STR062 = "Error in format or length of file";
char* STR063 = "Enter image name: ";
char* STR064 = "Ready ? (y/n): ";
char* STR065 = "Warning HALFSPEED MODE selected";
char* STR066 = "Geometry initialization error, cannot image";
char* STR067 = "Digitizing failed, no image made";
char* STR068 = "Use fscale command for this scale factor";
char* STR069 = "Warning: negative scale, effect is untested";
char* STR070 = "Warning: Scaling in sub-range, results may be unexpected";
char* STR071 = "Warning: Rshift has been altered";
char* STR072 = "Option specification required";
char* STR073 = "Warning: Entirely VOID longitude cannot be filled";
char* STR074 = "Warning: Entirely VOID latitude cannot be filled";
char* STR075 = "Error during open";
char* STR076 = "File protection error";
char* STR077 = "File not found";
char* STR078 = "Disc is Write-Protected";
char* STR079 = "Device is not accessible";
char* STR080 = "Error during file close";
char* STR081 = "Error with device or window";
char* STR082 = "Cannot allocate enough memory";
char* STR083 = "Type CONTROL_C key to stop";
char* STR084 = "'PASS COMPLETED'\r";    /* for the bridgeport */
char* STR085 = "Echo> ";                /* command line prompt */
char* STR086 = "Longitude increment";
char* STR087 = "Latitude increment";
char* STR088 = "Repeat terminated by error condition";
char* STR089 = "Horizontal Horizon Plot";
char* STR090 = "Horizontal Hemi-Cyl Plot";
char* STR091 = "Axial View of a Slice";
char* STR092 = "Cartesian Latitudes";
char* STR093 = "Cartesian Longitudes";
char* STR094 = "No options allowed, use 'display -s' command";
char* STR095 = "Move Mouse, left button to stop";
char* STR096 = "For menu press and hold right button";
char* STR097 = "Hold button, select item, release button";
char* STR098 = "Type a command, 'help' or 'exit'";
char* STR099 = "Move mouse, middle picks, left stops";
char* STR100 = "Use fscale command to scale cartesian data sets";
char* STR101 = "Error reading text string";
char* STR102 = "Cartesian/Cylindrical and data/command states do not match";
char* STR103 = "Machining parameters:";
char* STR104 = "Demo version, command not implemented";
char* STR105 = "Usage: echodemo image-pathname";
char* STR106 = "Undefined file header type";
char* STR107 = "Problem with file header";
char* STR108 = "Header seek error";
char* STR109 = "Header read error";
char* STR110 = "Header value not terminated properly";
char* STR111 = "Required value not in header";
char* STR112 = "Header value undefined";
char* STR113 = "Unexpected VOID";
char* STR114 = "Improper combination of options";
char* STR115 = "Step Offset      ";
char* STR116 = "Resolution Bits  ";
char* STR117 = "Sample Low Margin";
char* STR118 = "Sample Hi Margin ";
char* STR119 = "Server Name      ";
char* STR120 = "Set-up Date      ";
char* STR121 = "Unable to read optical configuration file";
char* STR122 = "Unable to read optical table file";
char* STR123 = "Optical parameter file seek error";
char* STR124 = "Optical parameter file read error";
char* STR125 = "Missing required optical parameter:";
char* STR126 = "Missing optical data table";
char* STR127 = "Please Standby - %d%% Complete\r";
char* STR128 = "                                \r";
char* STR129 = "Missing required mill parameter: %s\n";
char* STR130 = "Mill parameter file error";
char* STR131 = "Environment variable %s not defined\n";
char* STR132 = "Configuration file not found";
char* STR133 = "Cannot execute mill interface filter";
char* STR134 = "Cannot fork mill interface filter";
char* STR135 = "ECHO_MILL_TYPE incompatible with this command";
char* STR136 = "Unknown user";
char* STR137 = "File name must be given";
char* STR138 = "Environment variable has bad value: %s\n";
char* STR139 = "Command usage error, see manual";
char* STR140 = "Sorry, cannot find any information on \"%s\"\n";
char* STR141 = "References to \"%s\" found, try the manual page for:\n";
char* STR142 = "Server problem, frame receive";
char* STR143 = "Optical table format error";
char* STR144 = "Problem with SunView window system (Not a Sun terminal?)";
char* STR145 = "Image processing failed, no image made";
char* STR146 = "Longitude outside of current range window";
char* STR147 = "Latitude outside of current range window";
char* STR148 = "Tabulation of radii (mm/10) in latitude";
char* STR149 = "You must meter a point before clipping";
char* STR150 = "User Configuration file not found";
