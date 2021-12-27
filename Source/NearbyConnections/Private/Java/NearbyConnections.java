// Copyright (c) 2022 Nineva Studios

package com.ninevastudios.nearbyconnections;

import android.app.Activity;
import android.util.Log;

import androidx.annotation.NonNull;

import com.google.android.gms.common.api.Status;
import com.google.android.gms.nearby.Nearby;
import com.google.android.gms.nearby.connection.AdvertisingOptions;
import com.google.android.gms.nearby.connection.ConnectionInfo;
import com.google.android.gms.nearby.connection.ConnectionLifecycleCallback;
import com.google.android.gms.nearby.connection.ConnectionResolution;
import com.google.android.gms.nearby.connection.DiscoveredEndpointInfo;
import com.google.android.gms.nearby.connection.DiscoveryOptions;
import com.google.android.gms.nearby.connection.EndpointDiscoveryCallback;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;

public class NearbyConnections {
	private static final String TAG = "NearbyConnections";

	public static native void onStartAdvertisingSuccess();
	public static native void onStartAdvertisingError(String error);

	public static native void onConnectionInitiated(String endpointId, ConnectionInfo connectionInfo);
	public static native void onConnectionResult(String endpointId, int statusCode, String message);
	public static native void onDisconnected(String endpointId);

	public static native void onStartDiscoverySuccess();
	public static native void onStartDiscoveryError(String error);

	public static native void onEndpointFound(String endpointId, String serviceId, String endpointName, byte[] endpointInfo);
	public static native void onEndpointLost(String endpointId);

	public static void startAdvertising(Activity context, Options options, String userName, String serviceId) {
		AdvertisingOptions advertisingOptions = options.toAdvertisingOptions();
		if (advertisingOptions == null) {
			Log.e(TAG, "Wrong strategy passed to startAdvertising. Aborting operation.");
			return;
		}

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

	public static void startDiscovery(Activity context, Options options, String serviceId) {
		DiscoveryOptions discoveryOptions = options.toDiscoveryOptions();
		if (discoveryOptions == null) {
			Log.e(TAG, "Wrong strategy passed to startAdvertising. Aborting operation.");
			return;
		}

		Nearby.getConnectionsClient(context)
				.startDiscovery(serviceId, mEndpointDiscoveryCallback, discoveryOptions)
				.addOnSuccessListener(new OnSuccessListener<Void>() {
					@Override
					public void onSuccess(@NonNull Void unused) {
						onStartDiscoverySuccess();
					}
				})
				.addOnFailureListener(new OnFailureListener() {
					@Override
					public void onFailure(@NonNull Exception e) {
						onStartDiscoveryError(e.getMessage());
					}
				});
	}

	static ConnectionLifecycleCallback mConnectionLifecycleCallback = new ConnectionLifecycleCallback() {
		@Override
		public void onConnectionInitiated(@NonNull String endpointId, @NonNull ConnectionInfo connectionInfo) {
			NearbyConnections.onConnectionInitiated(endpointId, connectionInfo);
		}

		@Override
		public void onConnectionResult(@NonNull String endpointId, @NonNull ConnectionResolution connectionResolution) {
			Status status = connectionResolution.getStatus();
			NearbyConnections.onConnectionResult(endpointId, status.getStatusCode(), status.getStatusMessage());
		}

		@Override
		public void onDisconnected(@NonNull String endpointId) {
			NearbyConnections.onDisconnected(endpointId);
		}
	};

	static EndpointDiscoveryCallback mEndpointDiscoveryCallback = new EndpointDiscoveryCallback() {
		@Override
		public void onEndpointFound(@NonNull String endpointId, @NonNull DiscoveredEndpointInfo discoveredEndpointInfo) {
			NearbyConnections.onEndpointFound(
					endpointId,
					discoveredEndpointInfo.getServiceId(),
					discoveredEndpointInfo.getEndpointName(),
					discoveredEndpointInfo.getEndpointInfo());
		}

		@Override
		public void onEndpointLost(@NonNull String endpointId) {
			NearbyConnections.onEndpointLost(endpointId);
		}
	};
}