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
 
#ifndef __GST_MYFILTER_H__
#define __GST_MYFILTER_H__

#include <gst/gst.h>
#include <gst/base/gstbasetransform.h>

G_BEGIN_DECLS

#define GST_TYPE_MYFILTER \
  (gst_myfilter_get_type())
#define GST_MYFILTER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_MYFILTER,Gstmyfilter))
#define GST_MYFILTER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_MYFILTER,GstmyfilterClass))
#define GST_IS_MYFILTER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_MYFILTER))
#define GST_IS_MYFILTER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_MYFILTER))

typedef struct _Gstmyfilter      Gstmyfilter;
typedef struct _GstmyfilterClass GstmyfilterClass;

struct _Gstmyfilter {
  GstBaseTransform element;

  gboolean silent;
};

struct _GstmyfilterClass {
  GstBaseTransformClass parent_class;
};

GType gst_myfilter_get_type (void);

G_END_DECLS

#endif /* __GST_MYFILTER_H__ */
