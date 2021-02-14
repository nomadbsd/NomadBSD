package.path = "/usr/local/etc/dsbdriverd/?.lua;" .. package.path
netif = require("netif")

-- Configuration variables
--
-- This is a string list of kernel module names to exclude from loading
exclude_kmods = { "radeonkms", "amdgpu", "i915kms" }

-- This is a string list of network device to be ignored by the network
-- setup functions
-- ignore_netifs = { "ath0" }

-- This is a boolean variable which controls whether to auto configure
-- network devices
enable_netconfig = true

-- This is a boolean variable which controls whether IPv6 should be enabled
-- on the network interfaces.
enable_ipv6 = true

-- This variable defines the maximum number of seconds to wait for a network
-- interface to appear (after loading its driver).
netif_wait_max = 5

-- This is a boolean variable which controls whether to set country/region
-- on wlan devices
wlan_set_country = true

-- This is a string containing ifconfig arguments for creating a wlan device
-- wlan_create_args = ""

-- This is a string containing ifconfig arguments to start the wlan interfaces.
-- wlan_ifconfig_args = ""

-- This is a string containing ifconfig arguments to start the ethernet
-- interfaces.
-- ether_ifconfig_args = "DHCP"

-- This is a string containing ifconfig arguments to start the IPv6 ethernet
-- interfaces.
-- ether_ifconfig_ipv6_args = "inet6 accept_rtadv"

-- This is a string containing ifconfig arguments to start the IPv6 wlan
-- interfaces.
-- wlan_ifconfig_ipv6_args = "inet6 accept_rtadv"

------------------------------------------------------------------------------
-- Functions
--
-- Most functions take a device object as argument. A device object is a
-- data structure that contains the following fields:
-- 	bus ::= "1" | "2"
--		Where 1 stands for USB, and 2 stands for PCI
--	descr     ::= Device description string from the pciid/usbids DB.
--	vendor    ::= vendor ID
--	device    ::= device ID
--	subvendor ::= subvendor ID
--	subdevice ::= subdevice ID
--	class     ::= device class ID
--	subclass  ::= device subclass ID
--	revision  ::= Revision number
--	ndrivers  ::= Number of associated drivers in drivers[]
--	nifaces   ::= Number of USB interfaces
--	iface[]   ::= An array of "nifaces" USB interface objects (see below)
--	drivers[] ::= An array of associated drivers (strings).
--
-- The USB interface object structure contains the following fields:
--	class     ::= Device class ID
--	subclass  ::= Device subclass ID
--	protocol  ::= Device protocol
--

-- The init() function is run on startup before adding devices. It doesn't
-- take any arguments. The return value is ignored.
--
function init()
	if enable_netconfig then
		netif.setup_ether_devs()
		netif.create_wlan_devs()
	end
end

-- The on_load_kmod() function is called after loading a driver/kmod (string)
-- for the given device object. The return value is ignored. 
--
-- function on_load_kmod(dev, kmod)
-- end

-- The on_add_device() function is called every time a new device was added,
-- but before a driver was loaded. The return value is ignored.
--
-- function on_add_device(dev)
-- end
 
-- The affirm() function is called before loading a kmod.
-- If affirm() returns "true", the kmod will be loaded. Otherwise
-- loading is rejected.
--
-- function affirm(dev, kmod)
-- 	return true
-- end

-- The on_finished() function is called when all drivers for a device have
-- been loaded. The return value is ignored.
--
function on_finished(dev)
	local d, n
	if enable_netconfig then
		n = 0
		for _, d in pairs(dev.drivers) do
			netif.config_netif(d)
			n = n + 1
		end
		-- we might not have found a driver, but in case a new
		-- network interface appeared, try to set it up.
		if n == 0 then
			netif.setup_ether_devs()
			netif.create_wlan_devs()
		end
	end
end
