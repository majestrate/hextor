#! /usr/bin/python

# Hextor
# Copyright (C) 1998-2010 Peter Zelezny.
# Copyright (C) 2009-2013 Berke Viktor.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
#

import dbus

bus = dbus.SessionBus()
proxy = bus.get_object('org.hextor.service', '/org/hextor/Remote')
remote = dbus.Interface(proxy, 'org.hextor.connection')
path = remote.Connect ("example.py",
		       "Python example",
		       "Example of a D-Bus client written in python",
		       "1.0")
proxy = bus.get_object('org.hextor.service', path)
hextor = dbus.Interface(proxy, 'org.hextor.plugin')

channels = hextor.ListGet ("channels")
while hextor.ListNext (channels):
	name = hextor.ListStr (channels, "channel")
	print("------- " + name + " -------")
	hextor.SetContext (hextor.ListInt (channels, "context"))
	hextor.EmitPrint ("Channel Message", ["John", "Hi there", "@"])
	users = hextor.ListGet ("users")
	while hextor.ListNext (users):
		print("Nick: " + hextor.ListStr (users, "nick"))
	hextor.ListFree (users)
hextor.ListFree (channels)

print(hextor.Strip ("\00312Blue\003 \002Bold!\002", -1, 1|2))

