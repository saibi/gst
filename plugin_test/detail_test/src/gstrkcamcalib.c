/*
 * GStreamer
 * Copyright (C) 2005 Thomas Vander Stichele <thomas@apestaart.org>
 * Copyright (C) 2005 Ronald S. Bultje <rbultje@ronald.bitfreak.net>
 * Copyright (C) 2020 Youngmin Kim <<user@hostname.org>>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Alternatively, the contents of this file may be used under the
 * GNU Lesser General Public License Version 2.1 (the "LGPL"), in
 * which case the following provisions apply instead of the ones
 * mentioned above:
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * SECTION:element-rkcamcalib
 *
 * rkcam calibration plugin
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch -v -m fakesrc ! rkcamcalib ! fakesink silent=TRUE
 * ]|
 * </refsect2>
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gst/gst.h>

#include "gstrkcamcalib.h"

GST_DEBUG_CATEGORY_STATIC(gst_rkcam_calib_debug);
#define GST_CAT_DEFAULT gst_rkcam_calib_debug

/* Filter signals and args */
enum
{
	/* FILL ME */
	LAST_SIGNAL
};

enum
{
	PROP_0,
	PROP_SILENT
};

/* the capabilities of the inputs and outputs.
 *
 * describe the real formats here.
 */
static GstStaticPadTemplate sink_factory = GST_STATIC_PAD_TEMPLATE("sink",
								   GST_PAD_SINK,
								   GST_PAD_ALWAYS,
								   GST_STATIC_CAPS("ANY"));

static GstStaticPadTemplate src_factory = GST_STATIC_PAD_TEMPLATE("src",
								  GST_PAD_SRC,
								  GST_PAD_ALWAYS,
								  GST_STATIC_CAPS("ANY"));

#define gst_rkcam_calib_parent_class parent_class
G_DEFINE_TYPE(GstRkcamCalib, gst_rkcam_calib, GST_TYPE_ELEMENT);

static void gst_rkcam_calib_set_property(GObject * object, guint prop_id, const GValue * value, GParamSpec * pspec);
static void gst_rkcam_calib_get_property(GObject * object, guint prop_id, GValue * value, GParamSpec * pspec);

static gboolean gst_rkcam_calib_sink_event(GstPad * pad, GstObject * parent, GstEvent * event);


/* GObject vmethod implementations */

/* initialize the rkcamcalib's class */
static void gst_rkcam_calib_class_init(GstRkcamCalibClass * klass)
{
	GObjectClass *gobject_class;
	GstElementClass *gstelement_class;

	gobject_class = (GObjectClass *) klass;
	gstelement_class = (GstElementClass *) klass;

	gobject_class->set_property = gst_rkcam_calib_set_property;
	gobject_class->get_property = gst_rkcam_calib_get_property;

	g_object_class_install_property(gobject_class, PROP_SILENT, g_param_spec_boolean("silent", "Silent", "Produce verbose output ?", FALSE, G_PARAM_READWRITE));

// 1.0 api
	gst_element_class_set_static_metadata(gstelement_class, 
			"Rkcam Calib", 
			"Filter/Converter/Video", 
			"rkisp Camera Image Calibration Test", 
			"Youngmin Kim <<ymkim@huvitz.com>>");

// 0.1 api
#if 0
	gst_element_class_set_details_simple(gstelement_class, "RkcamCalib", "FIXME:Generic", "FIXME:Generic Template Element", "Youngmin Kim <<user@hostname.org>>");
#endif

	gst_element_class_add_pad_template(gstelement_class, gst_static_pad_template_get(&src_factory));
	gst_element_class_add_pad_template(gstelement_class, gst_static_pad_template_get(&sink_factory));
}

/* initialize the new element
 * instantiate pads and add them to element
 * set pad calback functions
 * initialize instance structure
 */
static void gst_rkcam_calib_init(GstRkcamCalib * filter)
{
	filter->sinkpad = gst_pad_new_from_static_template(&sink_factory, "sink");
	gst_pad_set_event_function(filter->sinkpad, GST_DEBUG_FUNCPTR(gst_rkcam_calib_sink_event));
	gst_pad_set_chain_function(filter->sinkpad, GST_DEBUG_FUNCPTR(gst_rkcam_calib_chain));
	GST_PAD_SET_PROXY_CAPS(filter->sinkpad);
	gst_element_add_pad(GST_ELEMENT(filter), filter->sinkpad);

	filter->srcpad = gst_pad_new_from_static_template(&src_factory, "src");
	GST_PAD_SET_PROXY_CAPS(filter->srcpad);
	gst_element_add_pad(GST_ELEMENT(filter), filter->srcpad);

	filter->silent = FALSE;
}

static void gst_rkcam_calib_set_property(GObject * object, guint prop_id, const GValue * value, GParamSpec * pspec)
{
	GstRkcamCalib *filter = GST_RKCAMCALIB(object);

	switch (prop_id)
	{
	case PROP_SILENT:
		filter->silent = g_value_get_boolean(value);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void gst_rkcam_calib_get_property(GObject * object, guint prop_id, GValue * value, GParamSpec * pspec)
{
	GstRkcamCalib *filter = GST_RKCAMCALIB(object);

	switch (prop_id)
	{
	case PROP_SILENT:
		g_value_set_boolean(value, filter->silent);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}


/* GstElement vmethod implementations */

/* this function handles sink events */
static gboolean gst_rkcam_calib_sink_event(GstPad * pad, GstObject * parent, GstEvent * event)
{
	GstRkcamCalib *filter;
	gboolean ret;

	filter = GST_RKCAMCALIB(parent);

	GST_LOG_OBJECT(filter, "Received %s event: %" GST_PTR_FORMAT, GST_EVENT_TYPE_NAME(event), event);

	switch (GST_EVENT_TYPE(event))
	{
	case GST_EVENT_CAPS:
	 {
		 GstCaps *caps;

		 gst_event_parse_caps(event, &caps);
		 /* do something with the caps */

		 print_caps(caps, "    ");
		 parse_cam_data_caps(caps);

		 /* and forward */
		 ret = gst_pad_event_default(pad, parent, event);
		 break;
	 }
	default:
		ret = gst_pad_event_default(pad, parent, event);
		break;
	}
	return ret;
}


/* entry point to initialize the plug-in
 * initialize the plug-in itself
 * register the element factories and other features
 */
static gboolean rkcamcalib_init(GstPlugin * rkcamcalib)
{
	/* debug category for fltering log messages
	 *
	 * exchange the string 'Template rkcamcalib' with your description
	 */
	GST_DEBUG_CATEGORY_INIT(gst_rkcam_calib_debug, "rkcamcalib", 0, "rkisp Camera Image Calibration Test");

	return gst_element_register(rkcamcalib, "rkcamcalib", GST_RANK_NONE, GST_TYPE_RKCAMCALIB);
}

/* PACKAGE: this is usually set by autotools depending on some _INIT macro
 * in configure.ac and then written into and defined in config.h, but we can
 * just set it ourselves here in case someone doesn't use autotools to
 * compile this code. GST_PLUGIN_DEFINE needs PACKAGE to be defined.
 */
#ifndef PACKAGE
#define PACKAGE "myfirstrkcamcalib"
#endif

/* gstreamer looks for this structure to register rkcamcalibs
 *
 * exchange the string 'Template rkcamcalib' with your rkcamcalib description
 */
GST_PLUGIN_DEFINE(GST_VERSION_MAJOR, GST_VERSION_MINOR, rkcamcalib, "rkisp Camera Image Calibration Test", rkcamcalib_init, VERSION, "LGPL", "GStreamer", "http://gstreamer.net/")
