
// Data structure to hold smart meter data, at least for meters 
// that comply with the Dutch DSMR standard (and also for some
// non-DSMR meters that do comply with IEC 62056-21).

#include <inttypes.h>

#define MAX_TARIFFS	2		// IEC 62056-21 allows 256, DSMR specifies just 2
#define MAX_PHASES	3
#define MAX_DEVS	4		// DSMR allows up to 4 M-bus devices
#define MAX_EVENTS	10		// DSMR allows max. 10 power failure events to be logged

#define LEN_HEADER			22		// '/' + 3 bytes vendor ID + 1 byte baud rate ID + max. 16 bytes model ID + '\0'
#define LEN_EQUIPMENT_ID	18		// 5 bytes meter ID + 10 bytes serial + 2 bytes year + '\0'
#define LEN_VALUE			33		// IEC 62056-21 allows max. 32 bytes
#define LEN_UNIT			17		// IEC 62056-21 allows max. 16 bytes
#define LEN_MESSAGE			2049	// DSMR allows max. 2048 bytes
#define LEN_MESSAGE_CODES	9		// DSMR allows max. 8 bytes

struct dsmr_data_struct {
	
	char header[LEN_HEADER];
	char equipment_id[LEN_EQUIPMENT_ID];
	
	uint32_t timestamp;
	
	int8_t 	P1_version_minor, P1_version_major;
	uint8_t	tariff;	
	int8_t 	switchpos;
	
	double		E_in[MAX_TARIFFS], 
				E_out[MAX_TARIFFS], 
				P_in_total, P_out_total, P_threshold,
				I[MAX_PHASES], I_threshold,
				V[MAX_PHASES], 
				P_in[MAX_PHASES], P_out[MAX_PHASES];
	
	char	unit_E_in[MAX_TARIFFS][LEN_UNIT], unit_E_out[MAX_TARIFFS][LEN_UNIT], 
			unit_P_in_total[LEN_UNIT], unit_P_out_total[LEN_UNIT], 
			unit_P_threshold[LEN_UNIT],
			unit_I[MAX_PHASES][LEN_UNIT], unit_I_threshold[LEN_UNIT],
			unit_V[MAX_PHASES][LEN_UNIT], 
			unit_P_in[MAX_PHASES][LEN_UNIT], unit_P_out[MAX_PHASES][LEN_UNIT];
		
	uint32_t	power_failures, power_failures_long,
				V_sags[MAX_PHASES], V_swells[MAX_PHASES];
	
	char	textmsg[LEN_MESSAGE], textmsg_codes[LEN_MESSAGE_CODES];
	
	uint8_t		dev_type[MAX_DEVS];
	int8_t		dev_valve[MAX_DEVS];
	double 		dev_counter[MAX_DEVS];
	uint32_t	dev_counter_timestamp[MAX_DEVS]
	char 		unit_dev_counter[MAX_DEVS][LEN_UNIT];
	char 		dev_id[MAX_DEVS][LEN_EQUIPMENT_ID];
	
	uint8_t		pfail_events;
	uint32_t	pfail_event_end_time[MAX_EVENTS];
	uint32_t	pfail_event_duration[MAX_EVENTS];
}