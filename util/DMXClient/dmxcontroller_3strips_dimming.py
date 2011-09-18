import wx
import dmx

ID_EXIT = wx.NewId()

class DMXFrame(wx.Frame):
    panel = None
    slider = None
    
    def __init__(self, parent, id):
        wx.Frame.__init__(self, parent, id, 'DMX RGB DIMMING TEST', size=(730,420))
        self.panel = wx.Panel(self)
            
        self.strip1_color = (0,0,0)
        self.strip2_color = (0,0,0)
        self.strip3_color = (0,0,0)
        self.strip4_color = (0,0,0)

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

        wx.StaticText(self.panel, -1, 'R', (offset+40,280))
        wx.StaticText(self.panel, -1, 'G', (offset+40*2,280))
        wx.StaticText(self.panel, -1, 'B', (offset+40*3,280))

        self.strip1_label = wx.StaticText(self.panel, -1, 'Strip1', (offset+40,300))
        font = wx.Font(20, wx.MODERN, wx.NORMAL, wx.BOLD)
        self.strip1_label.SetFont(font)

        wx.StaticLine(self.panel, -1, (offset+170, 30), (1,250),style=wx.LI_VERTICAL)

        #### Strip 2
        offset = 180
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

        #### Strip 3
        offset = 340 
        self.strip3_r_slider = wx.Slider(self.panel, -1, 0, 0, 255, pos=(offset+40,10), size=(-1 ,255), style= wx.SL_VERTICAL |wx.SL_AUTOTICKS | wx.SL_LABELS)
        self.strip3_r_slider.SetTickFreq(5, 1)
        self.strip3_g_slider = wx.Slider(self.panel, -1, 0, 0, 255, pos=(offset+40*2,10), size=(-1 ,255), style= wx.SL_VERTICAL |wx.SL_AUTOTICKS | wx.SL_LABELS)
        self.strip3_g_slider.SetTickFreq(5, 1)
        self.strip3_b_slider = wx.Slider(self.panel, -1, 0, 0, 255, pos=(offset+40*3,10), size=(-1 ,255), style= wx.SL_VERTICAL |wx.SL_AUTOTICKS | wx.SL_LABELS)
        self.strip3_b_slider.SetTickFreq(5, 1)


        wx.StaticText(self.panel, -1, 'R', (offset+40*1,280))
        wx.StaticText(self.panel, -1, 'G', (offset+40*2,280))
        wx.StaticText(self.panel, -1, 'B', (offset+40*3,280))

        self.strip3_label = wx.StaticText(self.panel, -1, 'Strip3', (20+offset,300))
        font = wx.Font(20, wx.MODERN, wx.NORMAL, wx.BOLD)
        self.strip3_label.SetFont(font)

        wx.StaticLine(self.panel, -1, (offset+170, 30), (1,250),style=wx.LI_VERTICAL)
        # Strip4
        offset = 500 
        self.strip4_r_slider = wx.Slider(self.panel, -1, 0, 0, 255, pos=(offset+40,10), size=(-1 ,255), style= wx.SL_VERTICAL |wx.SL_AUTOTICKS | wx.SL_LABELS)
        self.strip4_r_slider.SetTickFreq(5, 1)
        self.strip4_g_slider = wx.Slider(self.panel, -1, 0, 0, 255, pos=(offset+40*2,10), size=(-1 ,255), style= wx.SL_VERTICAL |wx.SL_AUTOTICKS | wx.SL_LABELS)
        self.strip4_g_slider.SetTickFreq(5, 1)
        self.strip4_b_slider = wx.Slider(self.panel, -1, 0, 0, 255, pos=(offset+40*3,10), size=(-1 ,255), style= wx.SL_VERTICAL |wx.SL_AUTOTICKS | wx.SL_LABELS)
        self.strip4_b_slider.SetTickFreq(5, 1)

        wx.StaticText(self.panel, -1, 'R', (offset+40*1,280))
        wx.StaticText(self.panel, -1, 'G', (offset+40*2,280))
        wx.StaticText(self.panel, -1, 'B', (offset+40*3,280))

        self.strip4_label = wx.StaticText(self.panel, -1, 'Strip4', (20+offset,300))
        font = wx.Font(20, wx.MODERN, wx.NORMAL, wx.BOLD)
        self.strip4_label.SetFont(font)


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

    def on_slider_update(self, event):
        # Strip 1 
        self.strip1_color = (self.strip1_r_slider.GetValue(), self.strip1_g_slider.GetValue(),self.strip1_b_slider.GetValue())
        self.strip1_label.SetForegroundColour(wx.Colour(*self.strip1_color))

        # Strip 2 
        self.strip2_color=(self.strip2_r_slider.GetValue() ,self.strip2_g_slider.GetValue() ,self.strip2_b_slider.GetValue())
        self.strip2_label.SetForegroundColour(wx.Colour(*self.strip2_color))

        # Strip 3 
        self.strip3_color=(self.strip3_r_slider.GetValue(),self.strip3_g_slider.GetValue(),self.strip3_b_slider.GetValue())
        self.strip3_label.SetForegroundColour(wx.Colour(*self.strip3_color))

        # Strip 4 
        self.strip4_color=(self.strip4_r_slider.GetValue(),self.strip4_g_slider.GetValue(),self.strip4_b_slider.GetValue())
        self.strip4_label.SetForegroundColour(wx.Colour(*self.strip4_color))
    
    # def on_dmx_update(self, event):
        self.dmx.write(100, self.strip1_color[0])
        self.dmx.write(101, self.strip1_color[1])
        self.dmx.write(102, self.strip1_color[2])

        self.dmx.write(105, self.strip2_color[0])
        self.dmx.write(106, self.strip2_color[1])
        self.dmx.write(107, self.strip2_color[2])

        self.dmx.write(110, self.strip3_color[0])
        self.dmx.write(111, self.strip3_color[1])
        self.dmx.write(112, self.strip3_color[2])

        self.dmx.write(115, self.strip4_color[0])
        self.dmx.write(116, self.strip4_color[1])
        self.dmx.write(117, self.strip4_color[2])
        

        self.dmx.update()

class DMXApp(wx.App):
    def OnInit(self):
        frame = DMXFrame(None, -1)
        frame.Show(True)
        self.SetTopWindow(frame)
        return True

app = DMXApp(0)
app.MainLoop()

