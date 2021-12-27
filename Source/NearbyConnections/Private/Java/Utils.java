package com.ninevastudios.nearbyconnections;

import com.google.android.gms.nearby.connection.Strategy;

public class Utils {
	static Strategy parseStrategy(int strategyInt) {
		if (strategyInt == 0)
			return Strategy.P2P_CLUSTER;
		if (strategyInt == 1)
			return Strategy.P2P_POINT_TO_POINT;
		if (strategyInt == 2)
			return Strategy.P2P_STAR;

		return null;
	}
}
