#ifndef BEEEON_ABSTRACT_COLLECTOR_H
#define BEEEON_ABSTRACT_COLLECTOR_H

#include "core/DistributorListener.h"
#include "zwave/ZWaveListener.h"

namespace BeeeOn {

/**
 * @brief The class represents a collector of events occuring inside the
 * Gateway. It implements all available listeners that can potentially
 * provide some interesting events about the Gateway and the connected
 * sensors.
 */
class AbstractCollector :
	public DistributorListener,
	public ZWaveListener {
public:
	virtual ~AbstractCollector();

	/**
	 * Empty implementation to be overrided if needed.
	 */
	void onExport(const SensorData &data) override;

	/**
	 * Empty implementation to be overrided if needed.
	 */
	void onDriverStats(const ZWaveDriverEvent &event) override;

	/**
	 * Empty implementation to be overrided if needed.
	 */
	void onNodeStats(const ZWaveNodeEvent &event) override;
};

}

#endif
