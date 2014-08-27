#!/usr/bin/python
from gi.repository import Gtk, Gdk, GObject

class MyWindow(Gtk.Window):

	def __init__(self):
		Gtk.Window.__init__(self, title="Hello World")
		self.set_size_request(200, 400)

		self.box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=6)
		self.add(self.box)
		
		self.my_accelerators = Gtk.AccelGroup()
		self.add_accel_group(self.my_accelerators)
		
		shift = Gdk.ModifierType.SHIFT_MASK
		ctrl = Gdk.ModifierType.CONTROL_MASK
		alt = Gdk.ModifierType.MOD1_MASK
		
		for tmp in [
				(alt | shift, ord('G')),
				(alt, ord('G')),
				(ctrl | shift, ord('R')),
				(ctrl, ord('R')),
				(ctrl, Gtk.accelerator_parse('Return')[0], 'Ctrl+Return'),
				(ctrl | alt | shift, ord('R')),
				(shift, ord('5')),
				(ctrl, ord('Q')),
				(ctrl, ord('+')),
				(ctrl, ord('Y')),
				(shift, ord(',')),
				(ctrl & shift, 0x00f8),
				(ctrl & shift, 0x0436),
			]:
			mod = tmp[0]
			key = tmp[1]
			label = ''
			if len(tmp) > 2:
				label = tmp[2]
			else:
				if mod & ctrl:
					label += 'Ctrl+'
				if mod & shift:
					label += 'Shift+'
				if mod & alt:
					label += 'Alt+'
				label += unichr(key)
			
			button = Gtk.Button(label=label)
			self.add_accelerator(button, mod, key)
			button.connect("clicked", self.on_button_clicked)
			self.box.pack_start(button, True, True, 0)

	def on_button_clicked(self, widget):
		print(widget.get_label())
		
	def add_accelerator(self, widget, mod, key, signal="activate"):
		if key == 0:
			key = ord(accelerator.lower()[len(accelerator)-1])
		print(widget.get_label(), key, mod)
		widget.add_accelerator(signal, self.my_accelerators, key, mod, Gtk.AccelFlags.VISIBLE)

win = MyWindow()
win.connect("delete-event", Gtk.main_quit)
win.show_all()
Gtk.main()