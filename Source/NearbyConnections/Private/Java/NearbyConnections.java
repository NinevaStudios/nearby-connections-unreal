// Copyright (c) 2022 Nineva Studios

package com.ninevastudios.nearbyconnections;

import android.app.Activity;
import android.util.Log;

import androidx.annotation.NonNull;

import com.google.android.gms.nearby.Nearby;
import com.google.android.gms.nearby.connection.AdvertisingOptions;
import com.google.android.gms.nearby.connection.ConnectionInfo;
import com.google.android.gms.nearby.connection.ConnectionLifecycleCallback;
import com.google.android.gms.nearby.connection.ConnectionResolution;
import com.google.android.gms.nearby.connection.Strategy;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;

public class NearbyConnections {
	private static final String TAG = "NearbyConnections";

	public static native void onStartAdvertisingSuccess();
	public static native void onStartAdvertisingError(String error);

	public static native void onConnectionInitiated(String endpointId, ConnectionInfo connectionInfo);
	public static native void onConnectionResult(String endpointId, ConnectionResolution connectionResolution);
	public static native void onDisconnected(String endpointId);

	public static void startAdvertising(Activity context, int strategyInt, String userName, String serviceId) {
		Strategy strategy = Utils.parseStrategy(strategyInt);
		if (strategy == null) {
			Log.e(TAG, "Wrong strategy passed to startAdvertising. Aborting operation.");
			return;
		}

		AdvertisingOptions advertisingOptions = new AdvertisingOptions.Builder().setStrategy(strategy).build();
		Nearby.getConnectionsClient(context)
				.startAdvertising(userName, serviceId, mConnectionLifecycleCallback, advertisingOptions)
				.addOnSuccessListener(new OnSuccessListener<Void>() {
					@Override
					public void onSuccess(@NonNull Void unused) {
						onStartAdvertisingSuccess();
					}
				})
				.addOnFailureListener(new OnFailureListener() {
					@Override
					public void onFailure(@NonNull Exception e) {
						onStartAdvertisingError(e.getMessage());
					}
				});
	}

	static ConnectionLifecycleCallback mConnectionLifecycleCallback = new ConnectionLifecycleCallback() {
		@Override
		public void onConnectionInitiated(@NonNull String endpointId, @NonNull ConnectionInfo connectionInfo) {
			onConnectionInitiated(endpointId, connectionInfo);
		}

		@Override
		public void onConnectionResult(@NonNull String endpointId, @NonNull ConnectionResolution connectionResolution) {
			onConnectionResult(endpointId, connectionResolution);
		}

		@Override
		public void onDisconnected(@NonNull String endpointId) {
			onDisconnected(endpointId);
		}
	};
}