#include "image_panel.h"

wxImagePanel::wxImagePanel(wxWindow* parent, wxString file, wxBitmapType format)
	: wxPanel(parent) {
    image.LoadFile(file, format);
	Connect(wxEVT_PAINT, wxPaintEventHandler(paintEvent));
}

void wxImagePanel::paintEvent(wxPaintEvent & evt) {
    wxPaintDC dc(this);
    render(dc);
}

void wxImagePanel::paintNow() {
    wxClientDC dc(this);
    render(dc);
}

void wxImagePanel::render(wxDC&  dc) {
    dc.DrawBitmap( image, 0, 0, false );
}
