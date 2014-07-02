/* -*- c++ -*- */
/*
 * Copyright 2012 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_QTGUI_FREQ_SINK_F_H
#define INCLUDED_QTGUI_FREQ_SINK_F_H

#ifdef ENABLE_PYTHON
#include <Python.h>
#endif

#include <gnuradio/qtgui/api.h>
#include <gnuradio/sync_block.h>
#include <qapplication.h>
#include <gnuradio/filter/firdes.h>

namespace gr {
  namespace qtgui {

    /*!
     * \brief A graphical sink to display multiple signals in frequency.
     * \ingroup instrumentation_blk
     * \ingroup qtgui_blk
     *
     * \details
     * This is a QT-based graphical sink the takes set of a floating
     * point streams and plots the PSD. Each signal is plotted with a
     * different color, and the \a set_title and \a set_color
     * functions can be used to change the lable and color for a given
     * input number.
     *
     * Message Ports:
     *
     * - freq (input):
     *        Receives a PMT pair: (intern("freq"), double(frequency).
     *        This is used to retune the center frequency of the
     *        display's x-axis.
     *
     * - freq (output):
     *        Produces a PMT pair with (intern("freq"), double(frequency).
     *        When a user double-clicks on the display, the frequency
     *        that the cursor is on is used to retune the x-axis scale
     *        to recenter onto the clicked frequency. A message
     *        containing the new frequency is also produced and can be
     *        used by other blocks to update their frequency setting.
     */
    class QTGUI_API freq_sink_f : virtual public sync_block
    {
    public:
      // gr::qtgui::freq_sink_f::sptr
      typedef boost::shared_ptr<freq_sink_f> sptr;

      /*!
       * \brief Build a floating point PSD sink.
       *
       * \param fftsize size of the FFT to compute and display
       * \param wintype type of window to apply (see gnuradio/filter/firdes.h)
       * \param fc center frequency of signal (use for x-axis labels)
       * \param bw bandwidth of signal (used to set x-axis labels)
       * \param name title for the plot
       * \param nconnections number of signals connected to sink
       * \param parent a QWidget parent object, if any
       */
      static sptr make(int fftsize, int wintype,
		       double fc, double bw,
		       const std::string &name,
		       int nconnections=1,
		       QWidget *parent=NULL);

      virtual void exec_() = 0;
      virtual QWidget* qwidget() = 0;

#ifdef ENABLE_PYTHON
      virtual PyObject* pyqwidget() = 0;
#else
      virtual void* pyqwidget() = 0;
#endif

      virtual void set_fft_size(const int fftsize) = 0;
      virtual int fft_size() const = 0;
      virtual void set_fft_average(const float fftavg) = 0;
      virtual float fft_average() const = 0;
      virtual void set_fft_window(const gr::filter::firdes::win_type win) = 0;
      virtual gr::filter::firdes::win_type fft_window() = 0;

      virtual void set_frequency_range(const double centerfreq, const double bandwidth) = 0;
      virtual void set_y_axis(double min, double max) = 0;

      virtual void set_update_time(double t) = 0;
      virtual void set_title(const std::string &title) = 0;
      virtual void set_line_label(int which, const std::string &label) = 0;
      virtual void set_line_color(int which, const std::string &color) = 0;
      virtual void set_line_width(int which, int width) = 0;
      virtual void set_line_style(int which, int style) = 0;
      virtual void set_line_marker(int which, int marker) = 0;
      virtual void set_line_alpha(int which, double alpha) = 0;

      virtual std::string title() = 0;
      virtual std::string line_label(int which) = 0;
      virtual std::string line_color(int which) = 0;
      virtual int line_width(int which) = 0;
      virtual int line_style(int which) = 0;
      virtual int line_marker(int which) = 0;
      virtual double line_alpha(int which) = 0;

      virtual void set_size(int width, int height) = 0;

      virtual void enable_menu(bool en=true) = 0;
      virtual void enable_grid(bool en=true) = 0;
      virtual void enable_autoscale(bool en=true) = 0;
      virtual void clear_max_hold() = 0;
      virtual void clear_min_hold() = 0;
      virtual void reset() = 0;

      QApplication *d_qApplication;
    };

  } /* namespace qtgui */
} /* namespace gr */

#endif /* INCLUDED_QTGUI_FREQ_SINK_F_H */
