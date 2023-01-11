#include "deepstream_config.h"
#include "deepstream_sinks.h"
#include "common/create_sink.hpp"
#include "config/config.hpp"


GstElement* Sink::Create(int current_sink_id){
  NvDsSinkBin *nvds_sink_bin = new NvDsSinkBin();
  NvDsSinkSubBinConfig *nvds_sink_sub_bin_configs = new NvDsSinkSubBinConfig();

  auto all_configs =  Config::Instance()->GetAllConfig();
  auto sink_config = all_configs["sink"];
  auto sink_list = sink_config["sink_list"];
  
  int number_sink = sink_list.size();

  for(auto i = 0; i< number_sink ; i++){
    auto sink = sink_list[i];
    int sink_id = sink["id"];
    
    if (sink_id != current_sink_id)
      continue;
    auto sink_type = NV_DS_SINK_UDPSINK;
    NvDsSinkSubBinConfig *nvdss_sink_bin_config = new NvDsSinkSubBinConfig();
    nvdss_sink_bin_config->enable = true;
    nvdss_sink_bin_config->source_id = current_sink_id;
    nvdss_sink_bin_config->type = sink_type;
    nvdss_sink_bin_config->sync = 1;
    if (sink_type == NV_DS_SINK_UDPSINK){

      NvDsSinkEncoderConfig sink_encode_config;
      sink_encode_config.type = NV_DS_SINK_UDPSINK;
      sink_encode_config.codec = NV_DS_ENCODER_H265;
      sink_encode_config.enc_type = NV_DS_ENCODER_TYPE_HW;
      sink_encode_config.bitrate = 4000000;
      sink_encode_config.profile = 0;
      sink_encode_config.sync = 0;
      sink_encode_config.gpu_id = 0;
      sink_encode_config.rtsp_port = 8554;
      sink_encode_config.udp_port = 9000;
      sink_encode_config.udp_buffer_size = 0;
      sink_encode_config.iframeinterval = 0;

      nvdss_sink_bin_config->encoder_config = sink_encode_config;
      NvDsSinkBinSubBin udp_sink;
      nvds_sink_bin->sub_bins[0] = udp_sink; // i->0
    }
    nvds_sink_sub_bin_configs[0] = *nvdss_sink_bin_config; // i-> 0
  }
  create_sink_bin(1, nvds_sink_sub_bin_configs, nvds_sink_bin,current_sink_id);
  return nvds_sink_bin->bin;
}