/* GStreamer unit test for dataurisrc
 *
 * Copyright (C) 2010 Tim-Philipp Müller <tim centricular net>
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

#include <unistd.h>

#include <gst/check/gstcheck.h>

/* sine wave encoded in ogg/vorbis, created with:
 *   gst-launch-0.10 audiotestsrc num-buffers=110 ! audioconvert ! \
 *                   audio/x-raw,channels=1 ! vorbisenc ! oggmux ! \
 *                   filesink location=sine.ogg
 * and then encoded to base64 */
const gchar data_uri[] = "data:audio/ogg;base64,"
    "T2dnUwACAAAAAAAAAACVWbd7AAAAAHgH02kBHgF2b3JiaXMAAAAAAUSsAAAAAAAAgDgBAAAAAAC4"
    "AU9nZ1MAAAAAAAAAAAAAlVm3ewEAAADrU8FRDkv///////////////+BA3ZvcmJpcx0AAABYaXBo"
    "Lk9yZyBsaWJWb3JiaXMgSSAyMDA5MDcwOQEAAAAaAAAAREVTQ1JJUFRJT049YXVkaW90ZXN0IHdh"
    "dmUBBXZvcmJpcyJCQ1YBAEAAACRzGCpGpXMWhBAaQlAZ4xxCzmvsGUJMEYIcMkxbyyVzkCGkoEKI"
    "WyiB0JBVAABAAACHQXgUhIpBCCGEJT1YkoMnPQghhIg5eBSEaUEIIYQQQgghhBBCCCGERTlokoMn"
    "QQgdhOMwOAyD5Tj4HIRFOVgQgydB6CCED0K4moOsOQghhCQ1SFCDBjnoHITCLCiKgsQwuBaEBDUo"
    "jILkMMjUgwtCiJqDSTX4GoRnQXgWhGlBCCGEJEFIkIMGQcgYhEZBWJKDBjm4FITLQagahCo5CB+E"
    "IDRkFQCQAACgoiiKoigKEBqyCgDIAAAQQFEUx3EcyZEcybEcCwgNWQUAAAEACAAAoEiKpEiO5EiS"
    "JFmSJVmSJVmS5omqLMuyLMuyLMsyEBqyCgBIAABQUQxFcRQHCA1ZBQBkAAAIoDiKpViKpWiK54iO"
    "CISGrAIAgAAABAAAEDRDUzxHlETPVFXXtm3btm3btm3btm3btm1blmUZCA1ZBQBAAAAQ0mlmqQaI"
    "MAMZBkJDVgEACAAAgBGKMMSA0JBVAABAAACAGEoOogmtOd+c46BZDppKsTkdnEi1eZKbirk555xz"
    "zsnmnDHOOeecopxZDJoJrTnnnMSgWQqaCa0555wnsXnQmiqtOeeccc7pYJwRxjnnnCateZCajbU5"
    "55wFrWmOmkuxOeecSLl5UptLtTnnnHPOOeecc84555zqxekcnBPOOeecqL25lpvQxTnnnE/G6d6c"
    "EM4555xzzjnnnHPOOeecIDRkFQAABABAEIaNYdwpCNLnaCBGEWIaMulB9+gwCRqDnELq0ehopJQ6"
    "CCWVcVJKJwgNWQUAAAIAQAghhRRSSCGFFFJIIYUUYoghhhhyyimnoIJKKqmooowyyyyzzDLLLLPM"
    "Ouyssw47DDHEEEMrrcRSU2011lhr7jnnmoO0VlprrbVSSimllFIKQkNWAQAgAAAEQgYZZJBRSCGF"
    "FGKIKaeccgoqqIDQkFUAACAAgAAAAABP8hzRER3RER3RER3RER3R8RzPESVREiVREi3TMjXTU0VV"
    "dWXXlnVZt31b2IVd933d933d+HVhWJZlWZZlWZZlWZZlWZZlWZYgNGQVAAACAAAghBBCSCGFFFJI"
    "KcYYc8w56CSUEAgNWQUAAAIACAAAAHAUR3EcyZEcSbIkS9IkzdIsT/M0TxM9URRF0zRV0RVdUTdt"
    "UTZl0zVdUzZdVVZtV5ZtW7Z125dl2/d93/d93/d93/d93/d9XQdCQ1YBABIAADqSIymSIimS4ziO"
    "JElAaMgqAEAGAEAAAIriKI7jOJIkSZIlaZJneZaomZrpmZ4qqkBoyCoAABAAQAAAAAAAAIqmeIqp"
    "eIqoeI7oiJJomZaoqZoryqbsuq7ruq7ruq7ruq7ruq7ruq7ruq7ruq7ruq7ruq7ruq7ruq4LhIas"
    "AgAkAAB0JEdyJEdSJEVSJEdygNCQVQCADACAAAAcwzEkRXIsy9I0T/M0TxM90RM901NFV3SB0JBV"
    "AAAgAIAAAAAAAAAMybAUy9EcTRIl1VItVVMt1VJF1VNVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV"
    "VVVVVVVVVVVN0zRNEwgNWQkAAAEA0FpzzK2XjkHorJfIKKSg10455qTXzCiCnOcQMWOYx1IxQwzG"
    "lkGElAVCQ1YEAFEAAIAxyDHEHHLOSeokRc45Kh2lxjlHqaPUUUqxplo7SqW2VGvjnKPUUcoopVpL"
    "qx2lVGuqsQAAgAAHAIAAC6HQkBUBQBQAAIEMUgophZRizinnkFLKOeYcYoo5p5xjzjkonZTKOSed"
    "kxIppZxjzinnnJTOSeack9JJKAAAIMABACDAQig0ZEUAECcA4HAcTZM0TRQlTRNFTxRd1xNF1ZU0"
    "zTQ1UVRVTRRN1VRVWRZNVZYlTTNNTRRVUxNFVRVVU5ZNVbVlzzRt2VRV3RZV1bZlW/Z9V5Z13TNN"
    "2RZV1bZNVbV1V5Z1XbZt3Zc0zTQ1UVRVTRRV11RV2zZV1bY1UXRdUVVlWVRVWXZdWddVV9Z9TRRV"
    "1VNN2RVVVZZV2dVlVZZ1X3RV3VZd2ddVWdZ929aFX9Z9wqiqum7Krq6rsqz7si77uu3rlEnTTFMT"
    "RVXVRFFVTVe1bVN1bVsTRdcVVdWWRVN1ZVWWfV91ZdnXRNF1RVWVZVFVZVmVZV13ZVe3RVXVbVV2"
    "fd90XV2XdV1YZlv3hdN1dV2VZd9XZVn3ZV3H1nXf90zTtk3X1XXTVXXf1nXlmW3b+EVV1XVVloVf"
    "lWXf14XheW7dF55RVXXdlF1fV2VZF25fN9q+bjyvbWPbPrKvIwxHvrAsXds2ur5NmHXd6BtD4TeG"
    "NNO0bdNVdd10XV+Xdd1o67pQVFVdV2XZ91VX9n1b94Xh9n3fGFXX91VZFobVlp1h932l7guVVbaF"
    "39Z155htXVh+4+j8vjJ0dVto67qxzL6uPLtxdIY+AgAABhwAAAJMKAOFhqwIAOIEABiEnENMQYgU"
    "gxBCSCmEkFLEGITMOSkZc1JCKamFUlKLGIOQOSYlc05KKKGlUEpLoYTWQimxhVJabK3VmlqLNYTS"
    "WiiltVBKi6mlGltrNUaMQcick5I5J6WU0loopbXMOSqdg5Q6CCmllFosKcVYOSclg45KByGlkkpM"
    "JaUYQyqxlZRiLCnF2FpsucWYcyilxZJKbCWlWFtMObYYc44Yg5A5JyVzTkoopbVSUmuVc1I6CCll"
    "DkoqKcVYSkoxc05KByGlDkJKJaUYU0qxhVJiKynVWEpqscWYc0sx1lBSiyWlGEtKMbYYc26x5dZB"
    "aC2kEmMoJcYWY66ttRpDKbGVlGIsKdUWY629xZhzKCXGkkqNJaVYW425xhhzTrHlmlqsucXYa225"
    "9Zpz0Km1WlNMubYYc465BVlz7r2D0FoopcVQSoyttVpbjDmHUmIrKdVYSoq1xZhza7H2UEqMJaVY"
    "S0o1thhrjjX2mlqrtcWYa2qx5ppz7zHm2FNrNbcYa06x5Vpz7r3m1mMBAAADDgAAASaUgUJDVgIA"
    "UQAABCFKMQahQYgx56Q0CDHmnJSKMecgpFIx5hyEUjLnIJSSUuYchFJSCqWkklJroZRSUmqtAACA"
    "AgcAgAAbNCUWByg0ZCUAkAoAYHAcy/I8UTRV2XYsyfNE0TRV1bYdy/I8UTRNVbVty/NE0TRV1XV1"
    "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";

GST_START_TEST (test_playbin)
{
  GstElement *playbin, *sink;
  int loops = 2;

  playbin = gst_element_factory_make ("playbin", NULL);
  sink = gst_element_factory_make ("fakesink", NULL);

  if (playbin == NULL || sink == NULL) {
    GST_WARNING ("skipping test, no playbin or fakesink element(s)");
    return;
  }

  g_object_set (playbin, "uri", data_uri, "audio-sink", sink, NULL);

  do {
    GstMessage *msg;

    /* not checking return val on purpose, should always get an error on bus */
    gst_element_set_state (playbin, GST_STATE_PLAYING);

    msg = gst_bus_timed_pop_filtered (GST_ELEMENT_BUS (playbin),
        GST_CLOCK_TIME_NONE, GST_MESSAGE_EOS | GST_MESSAGE_ERROR);

    GST_INFO ("message: %" GST_PTR_FORMAT, msg);
    if (GST_MESSAGE_TYPE (msg) == GST_MESSAGE_ERROR) {
      GError *err = NULL;

      gst_message_parse_error (msg, &err, NULL);
      fail_unless (err->code == GST_CORE_ERROR_MISSING_PLUGIN ||
          err->code == GST_STREAM_ERROR_CODEC_NOT_FOUND,
          "Got unexpected error: %s", err->message);
      g_error_free (err);
    }

    gst_message_unref (msg);
    gst_element_set_state (playbin, GST_STATE_NULL);

    --loops;
    GST_INFO ("done, %d rounds left", loops);
  } while (loops > 0);

  gst_element_set_state (playbin, GST_STATE_NULL);
  gst_object_unref (playbin);
}

GST_END_TEST;

static Suite *
dataurisrc_suite (void)
{
  Suite *s = suite_create ("dataurisrc");
  TCase *tc_chain = tcase_create ("general");

  suite_add_tcase (s, tc_chain);

  tcase_add_test (tc_chain, test_playbin);

  return s;
}

GST_CHECK_MAIN (dataurisrc);
