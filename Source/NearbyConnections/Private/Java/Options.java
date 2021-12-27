package com.ninevastudios.nearbyconnections;

import com.google.android.gms.nearby.connection.AdvertisingOptions;
import com.google.android.gms.nearby.connection.DiscoveryOptions;
import com.google.android.gms.nearby.connection.Strategy;

public class Options {
	Strategy strategy;
	boolean isLowPower, isDisruptiveUpgrade;

	public Options(int strategyInt, boolean isLowPower, boolean isDisruptiveUpgrade) {
		strategy = Utils.parseStrategy(strategyInt);
		this.isLowPower = isLowPower;
		this.isDisruptiveUpgrade = isDisruptiveUpgrade;
	}

	public AdvertisingOptions toAdvertisingOptions() {
		if (strategy == null) {
			return null;
		}

		return new AdvertisingOptions.Builder()
				.setStrategy(strategy)
				.setLowPower(isLowPower)
				.setDisruptiveUpgrade(isDisruptiveUpgrade)
				.build();
	}

	public DiscoveryOptions toDiscoveryOptions() {
		if (strategy == null) {
			return null;
		}

		return new DiscoveryOptions.Builder()
				.setStrategy(strategy)
				.setLowPower(isLowPower)
				.build();
	}
}
