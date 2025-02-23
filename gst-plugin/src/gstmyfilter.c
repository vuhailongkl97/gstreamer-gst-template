/*
 * GStreamer
 * Copyright (C) 2006 Stefan Kost <ensonic@users.sf.net>
 * Copyright (C) 2023 long <<user@hostname.org>>
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
 * SECTION:element-myfilter
 *
 * FIXME:Describe myfilter here.
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch -v -m fakesrc ! myfilter ! fakesink silent=TRUE
 * ]|
 * </refsect2>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>
#include <gst/base/base.h>
#include <gst/controller/controller.h>

#include "gstmyfilter.h"

GST_DEBUG_CATEGORY_STATIC (gst_myfilter_debug);
#define GST_CAT_DEFAULT gst_myfilter_debug

/* Filter signals and args */
enum
{
  /* FILL ME */
  LAST_SIGNAL
};

enum
{
  PROP_0,
  PROP_SILENT,
};

/* the capabilities of the inputs and outputs.
 *
 * FIXME:describe the real formats here.
 */
static GstStaticPadTemplate sink_template =
GST_STATIC_PAD_TEMPLATE (
  "sink",
  GST_PAD_SINK,
  GST_PAD_ALWAYS,
  GST_STATIC_CAPS ("ANY")
);

static GstStaticPadTemplate src_template =
GST_STATIC_PAD_TEMPLATE (
  "src",
  GST_PAD_SRC,
  GST_PAD_ALWAYS,
  GST_STATIC_CAPS ("ANY")
);

#define gst_myfilter_parent_class parent_class
G_DEFINE_TYPE (Gstmyfilter, gst_myfilter, GST_TYPE_BASE_TRANSFORM);

static void gst_myfilter_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec);
static void gst_myfilter_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec);

static GstFlowReturn gst_myfilter_transform_ip (GstBaseTransform * base,
    GstBuffer * outbuf);

/* GObject vmethod implementations */
static gboolean
 gst_myfilter_start(GstBaseTransform * btrans) {
	g_print("go to myfilter start\n");
	return TRUE;
}

static gboolean
gst_myfilter_stop (GstBaseTransform * btrans) {
	g_print("go to myfilter stop\n");
	return TRUE;
}
static gboolean
gst_myfilter_set_caps (GstBaseTransform * btrans, GstCaps * incaps,
					       GstCaps * outcaps) {
	return TRUE;
}
/* initialize the myfilter's class */
static void
gst_myfilter_class_init (GstmyfilterClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *gstelement_class;

  gobject_class = (GObjectClass *) klass;
  gstelement_class = (GstElementClass *) klass;

  gobject_class->set_property = gst_myfilter_set_property;
  gobject_class->get_property = gst_myfilter_get_property;

  g_object_class_install_property (gobject_class, PROP_SILENT,
    g_param_spec_boolean ("silent", "Silent", "Produce verbose output ?",
          FALSE, G_PARAM_READWRITE | GST_PARAM_CONTROLLABLE));

  gst_element_class_set_details_simple (gstelement_class,
    "myfilter",
    "Generic/Filter",
    "FIXME:Generic Template Filter",
    "long <<user@hostname.org>>");

  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&src_template));
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&sink_template));

  GST_BASE_TRANSFORM_CLASS(klass)->set_caps = GST_DEBUG_FUNCPTR (gst_myfilter_set_caps);
  GST_BASE_TRANSFORM_CLASS(klass)->start = GST_DEBUG_FUNCPTR (gst_myfilter_start);
  GST_BASE_TRANSFORM_CLASS(klass)->stop = GST_DEBUG_FUNCPTR (gst_myfilter_stop);
  GST_BASE_TRANSFORM_CLASS (klass)->transform_ip =
      GST_DEBUG_FUNCPTR (gst_myfilter_transform_ip);

  /* debug category for fltering log messages
   *
   * FIXME:exchange the string 'Template myfilter' with your description
   */
  GST_DEBUG_CATEGORY_INIT (gst_myfilter_debug, "myfilter", 0, "Template myfilter");
}

/* initialize the new element
 * initialize instance structure
 */
static void
gst_myfilter_init (Gstmyfilter *filter)
{
  filter->silent = FALSE;
}

static void
gst_myfilter_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  Gstmyfilter *filter = GST_MYFILTER (object);

  switch (prop_id) {
    case PROP_SILENT:
      filter->silent = g_value_get_boolean (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_myfilter_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  Gstmyfilter *filter = GST_MYFILTER (object);

  switch (prop_id) {
    case PROP_SILENT:
      g_value_set_boolean (value, filter->silent);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

/* GstBaseTransform vmethod implementations */

/* this function does the actual processing
 */
static GstFlowReturn
gst_myfilter_transform_ip (GstBaseTransform * base, GstBuffer * outbuf)
{
  Gstmyfilter *filter = GST_MYFILTER (base);
  GstMapInfo map_out;

  GST_LOG_OBJECT (filter, "transform buffer");

    if (gst_buffer_map (outbuf, &map_out, GST_MAP_WRITE)) {
      memset(map_out.data, 255, map_out.size);
      gst_buffer_unmap (outbuf, &map_out);
    }

  return GST_FLOW_OK;

  //if (GST_CLOCK_TIME_IS_VALID (GST_BUFFER_TIMESTAMP (outbuf)))
  //  gst_object_sync_values (GST_OBJECT (filter), GST_BUFFER_TIMESTAMP (outbuf));

//  if (filter->silent == FALSE)
 //   g_print ("I'm plugged, therefore I'm in.\n");
  //gsize s = gst_buffer_get_size(outbuf);
  //g_print("%ld\n", outbuf->offset);
  //gst_buffer_set_size(outbuf, 1000);
  
  /* FIXME: do something interesting here.  This simply copies the source
   * to the destination. */

  return GST_FLOW_OK;
}


/* entry point to initialize the plug-in
 * initialize the plug-in itself
 * register the element factories and other features
 */
static gboolean
myfilter_init (GstPlugin * myfilter)
{
  return gst_element_register (myfilter, "myfilter", GST_RANK_NONE,
      GST_TYPE_MYFILTER);
}

/* gstreamer looks for this structure to register myfilters
 *
 * FIXME:exchange the string 'Template myfilter' with you myfilter description
 */
GST_PLUGIN_DEFINE (
    GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    myfilter,
    "Template myfilter",
    myfilter_init,
    VERSION,
    "LGPL",
    "GStreamer",
    "http://gstreamer.net/"
)
