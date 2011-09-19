import wx
import dmx

ID_EXIT = wx.NewId()

class DMXFrame(wx.Frame):
    panel = None
    slider = None
    
    def __init__(self, parent, id):
        wx.Frame.__init__(self, parent, id, 'ARM DMX DEMO', size=(730,420))
        self.panel = wx.Panel(self)
            
        self.strip1_color = (0,0,0)
        self.strip1_mode = 0
        self.strip1_speed = 0
        self.strip1_dimming = 0

        self.strip2_color = (0,0,0)
        self.strip2_mode = 0
        self.strip2_speed = 0
        self.strip2_dimming = 0

        # self.timer = wx.Timer(self, 1)
        # self.Bind(wx.EVT_TIMER, self.on_dmx_update, self.timer)

        # fetm logo
        self.logo = wx.Bitmap('fetm50.jpg')
        wx.StaticBitmap(self.panel, -5, self.logo, pos=(665,325))

        # Strip 1
        offset = 20
        self.strip1_r_slider = wx.Slider(self.panel, -1, 0, 0, 255, pos=(offset+40,10), size=(-1 ,255), style= wx.SL_VERTICAL |wx.SL_AUTOTICKS | wx.SL_LABELS)
        self.strip1_r_slider.SetTickFreq(5, 1)
        self.strip1_g_slider = wx.Slider(self.panel, -1, 0, 0, 255, pos=(offset+40*2,10), size=(-1 ,255), style= wx.SL_VERTICAL |wx.SL_AUTOTICKS | wx.SL_LABELS)
        self.strip1_g_slider.SetTickFreq(5, 1)
        self.strip1_b_slider = wx.Slider(self.panel, -1, 0, 0, 255, pos=(offset+40*3,10), size=(-1 ,255), style= wx.SL_VERTICAL |wx.SL_AUTOTICKS | wx.SL_LABELS)
        self.strip1_b_slider.SetTickFreq(5, 1)

        self.strip1_speed_slider = wx.Slider(self.panel, -1, 0, 0, 255, pos=(offset+40*4,10), size=(-1 ,255), style= wx.SL_VERTICAL |wx.SL_AUTOTICKS | wx.SL_LABELS)
        self.strip1_speed_slider.SetTickFreq(5, 1)

        self.strip1_dimming_slider = wx.Slider(self.panel, -1, 0, 0, 255, pos=(offset+40*5,10), size=(-1 ,255), style= wx.SL_VERTICAL |wx.SL_AUTOTICKS | wx.SL_LABELS)
        self.strip1_dimming_slider.SetTickFreq(5, 1)

        wx.StaticText(self.panel, -1, 'R', (offset+40,280))
        wx.StaticText(self.panel, -1, 'G', (offset+40*2,280))
        wx.StaticText(self.panel, -1, 'B', (offset+40*3,280))
        wx.StaticText(self.panel, -1, 'S', (offset+40*4,280))
        wx.StaticText(self.panel, -1, 'D', (offset+40*5,280))

        self.strip1_label = wx.StaticText(self.panel, -1, 'Strip1', (offset+40,300))
        font = wx.Font(20, wx.MODERN, wx.NORMAL, wx.BOLD)
        self.strip1_label.SetFont(font)


        self.cb = wx.CheckBox(self.panel, -1, '(direct/flow)', (offset+230, 40))
        self.cb.SetValue(True)
        wx.EVT_CHECKBOX(self, self.cb.GetId(), self.on_set_mode)

        wx.StaticLine(self.panel, -1, (offset+350, 30), (1,250),style=wx.LI_VERTICAL)
        
        #### Strip 2
        offset = 350
        self.strip2_r_slider = wx.Slider(self.panel, -1, 0, 0, 255, pos=(offset+40,10), size=(-1 ,255), style= wx.SL_VERTICAL |wx.SL_AUTOTICKS | wx.SL_LABELS)
        self.strip2_r_slider.SetTickFreq(5, 1)
        self.strip2_g_slider = wx.Slider(self.panel, -1, 0, 0, 255, pos=(offset+40*2,10), size=(-1 ,255), style= wx.SL_VERTICAL |wx.SL_AUTOTICKS | wx.SL_LABELS)
        self.strip2_g_slider.SetTickFreq(5, 1)
        self.strip2_b_slider = wx.Slider(self.panel, -1, 0, 0, 255, pos=(offset+40*3,10), size=(-1 ,255), style= wx.SL_VERTICAL |wx.SL_AUTOTICKS | wx.SL_LABELS)
        self.strip2_b_slider.SetTickFreq(5, 1)

        wx.StaticText(self.panel, -1, 'R', (offset+40*1,280))
        wx.StaticText(self.panel, -1, 'G', (offset+40*2,280))
        wx.StaticText(self.panel, -1, 'B', (offset+40*3,280))


        self.strip2_label = wx.StaticText(self.panel, -1, 'Strip2', (20+offset,300))
        font = wx.Font(20, wx.MODERN, wx.NORMAL, wx.BOLD)
        self.strip2_label.SetFont(font)

        wx.StaticLine(self.panel, -1, (offset+170, 30), (1,250),style=wx.LI_VERTICAL)


        ## Slider Event
        self.Bind(wx.EVT_SLIDER, self.on_slider_update)


        # Menu
        self.menubar = wx.MenuBar()
        self.SetMenuBar(self.menubar)

        _menu = wx.Menu()
        _menu.Append(ID_EXIT, "&Exit", "", wx.ITEM_NORMAL)
        self.Bind(wx.EVT_MENU, self.on_close, id= ID_EXIT)
        self.menubar.Append(_menu, "&File")

        _menu = wx.Menu()
        _menu.Append(ID_EXIT, "&About", "", wx.ITEM_NORMAL)
        self.menubar.Append(_menu, "&About")

        # DMX initialize

        self.dmx = dmx.DMX()
	    #self.dmx.open('com1')
        self.dmx.open('/dev/ttyUSB0')
        self.dmx.start_thread()

    def on_close(self, event):
        self.Close()

    def on_set_mode(self, event):
        # Strip 1 
        direct=self.cb.GetValue()
        if direct:
            self.strip1_mode = 0 # direct
        else:
            self.strip1_mode = 1 # dot-flow
        self.on_dmx_update(0)

    def on_slider_update(self, event):
        # Strip 1 
        self.strip1_color = (self.strip1_g_slider.GetValue(),self.strip1_b_slider.GetValue(),self.strip1_r_slider.GetValue())
        self.strip1_label.SetForegroundColour(wx.Colour(*self.strip1_color))

        self.strip1_speed = self.strip1_speed_slider.GetValue()

        # Strip 2 
        self.strip2_color = (self.strip2_g_slider.GetValue(),self.strip2_b_slider.GetValue(),self.strip2_r_slider.GetValue())
        self.strip2_label.SetForegroundColour(wx.Colour(*self.strip2_color))

        # self.strip2_speed = self.strip2_speed_slider.GetValue()

        self.on_dmx_update(0)

    def on_dmx_update(self, event):
        self.dmx.write(100, self.strip1_color[0])
        self.dmx.write(101, self.strip1_color[1])
        self.dmx.write(102, self.strip1_color[2])
        self.dmx.write(103, self.strip1_mode)
        self.dmx.write(104, self.strip1_speed)
        self.dmx.write(105, self.strip1_dimming)

        self.dmx.write(106, self.strip2_color[0])
        self.dmx.write(107, self.strip2_color[1])
        self.dmx.write(108, self.strip2_color[2])
        self.dmx.write(109, self.strip2_mode)
        self.dmx.write(110, self.strip2_speed)
        self.dmx.write(111, self.strip2_dimming)

        self.dmx.update()

class DMXApp(wx.App):
    def OnInit(self):
        frame = DMXFrame(None, -1)
        frame.Show(True)
        self.SetTopWindow(frame)
        return True

app = DMXApp(0)
app.MainLoop()

