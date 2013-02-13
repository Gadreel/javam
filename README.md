# JavaM #

## A Java binding to the GT.M language and database ##

Version 0.1 - 2013 Feb 13

## Copyright and License ##

Written by Andy White <andy@etimeline.com>
Copyright © 2013 eTimeline, LLC

Originally based on code written by David Wicksell <dlw@linux.com>  
https://github.com/dlwicksell/nodem
Copyright © 2012,2013 Fourth Watch Software, LC

Also based on code written by Lothar Joeckel
http://code.vistaehr.com/gtm4j
Copyright © 2012

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License (AGPL)
as published by the Free Software Foundation, either version 3 of
the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

***

## Summary and Info ##

This project was inspired by Nodem (https://github.com/dlwicksell/nodem)
however after a bit of hacking it barely resembles that project.

The idea is to give a proof of concept for Java binding to GT.M using the
call-in interface.  The hope was to provide many of the features of Nodem
even if not the same syntax (all JSON like structures are removed for this 
proof of concept).

I certainly wouldn't use this in production as is, but it may give some 
interesting ideas to anyone contemplating the Java to M binding.

## Installation ##

If you are serious about this project you should review the notes at Nodem 
(https://github.com/dlwicksell/nodem).

If you just want to try something out then clone the project to a 64 bit
Linux box (I was using Amazon Linux).  Obviously you need GT.M installed 
too.  Edit the file "bin/run.sh" and switch line 5 to point to your GT.M 
distro path (mine was "/usr/local/gtm").  Give "bin/run.sh" execute 
permissions.  Run it:

>vi run.sh

[fix >source /usr/local/gtm/gtmprofile]

>chmod 700 run.sh

>./run.sh

You should then see output from the Java to M calls.  Sets, gets, $d, $i,
$o and function calls are tested.

