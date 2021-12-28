// Copyright (c) 2022 Nineva Studios

package com.ninevastudios.nearbyconnections;

import android.app.Activity;
import android.net.Uri;
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
import com.google.android.gms.nearby.connection.Payload;
import com.google.android.gms.nearby.connection.PayloadCallback;
import com.google.android.gms.nearby.connection.PayloadTransferUpdate;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;

@SuppressWarnings("unused")
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

	public static native void onAcceptConnectionSuccess();
	public static native void onAcceptConnectionError(String error);

	public static native void onPayloadReceived(String endpointId, Payload payload);
	public static native void onPayloadTransferUpdate(String endpointId, PayloadTransferUpdate payloadTransferUpdate);

	public static native void onRequestConnectionSuccess();
	public static native void onRequestConnectionError(String error);

	public static native void onSendPayloadSuccess();
	public static native void onSendPayloadError(String error);

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

	public static void stopAdvertising(Activity context) {
		Nearby.getConnectionsClient(context).stopAdvertising();
	}

	public static void startDiscovery(Activity context, Options options, String serviceId) {
		DiscoveryOptions discoveryOptions = options.toDiscoveryOptions();
		if (discoveryOptions == null) {
			Log.e(TAG, "Wrong strategy passed to startDiscovery. Aborting operation.");
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

	public static void stopDiscovery(Activity context) {
		Nearby.getConnectionsClient(context).stopDiscovery();
	}

	public static void stopAllEndpoints(Activity context) {
		Nearby.getConnectionsClient(context).stopAllEndpoints();
	}

	public static void acceptConnection(Activity context, String endpointId) {
		Nearby.getConnectionsClient(context).acceptConnection(endpointId, mPayloadCallback)
				.addOnSuccessListener(new OnSuccessListener<Void>() {
					@Override
					public void onSuccess(@NonNull Void unused) {
						onAcceptConnectionSuccess();
					}
				})
				.addOnFailureListener(new OnFailureListener() {
					@Override
					public void onFailure(@NonNull Exception e) {
						onAcceptConnectionError(e.getMessage());
					}
				});
	}

	public static void cancelPayload(Activity context, long payloadId) {
		Nearby.getConnectionsClient(context).cancelPayload(payloadId);
	}

	public static void disconnectFromEndpoint(Activity context, String endpointId) {
		Nearby.getConnectionsClient(context).disconnectFromEndpoint(endpointId);
	}

	public static void rejectConnection(Activity context, String endpointId) {
		Nearby.getConnectionsClient(context).rejectConnection(endpointId)
				.addOnSuccessListener(new OnSuccessListener<Void>() {
					@Override
					public void onSuccess(@NonNull Void unused) {
						onAcceptConnectionSuccess();
					}
				})
				.addOnFailureListener(new OnFailureListener() {
					@Override
					public void onFailure(@NonNull Exception e) {
						onAcceptConnectionError(e.getMessage());
					}
				});
	}

	public static void requestConnection(Activity context, String name, String endpointId, Options options) {
		Nearby.getConnectionsClient(context).requestConnection(name, endpointId, mConnectionLifecycleCallback, options.toConnectionOptions())
				.addOnSuccessListener(new OnSuccessListener<Void>() {
					@Override
					public void onSuccess(@NonNull Void unused) {
						onRequestConnectionSuccess();
					}
				})
				.addOnFailureListener(new OnFailureListener() {
					@Override
					public void onFailure(@NonNull Exception e) {
						onRequestConnectionError(e.getMessage());
					}
				});
	}

	public static void requestConnection(Activity context, byte[] endpointInfo, String endpointId, Options options) {
		Nearby.getConnectionsClient(context).requestConnection(endpointInfo, endpointId, mConnectionLifecycleCallback, options.toConnectionOptions())
				.addOnSuccessListener(new OnSuccessListener<Void>() {
					@Override
					public void onSuccess(@NonNull Void unused) {
						onRequestConnectionSuccess();
					}
				})
				.addOnFailureListener(new OnFailureListener() {
					@Override
					public void onFailure(@NonNull Exception e) {
						onRequestConnectionError(e.getMessage());
					}
				});
	}

	public static void sendPayload(Activity context, Payload payload, String[] endpoints) {
		Nearby.getConnectionsClient(context).sendPayload(Arrays.asList(endpoints), payload)
				.addOnSuccessListener(new OnSuccessListener<Void>() {
					@Override
					public void onSuccess(@NonNull Void unused) {
						onSendPayloadSuccess();
					}
				})
				.addOnFailureListener(new OnFailureListener() {
					@Override
					public void onFailure(@NonNull Exception e) {
						onSendPayloadError(e.getMessage());
					}
				});
	}

	public static Payload payloadFromBytes(byte[] bytes) {
		return Payload.fromBytes(bytes);
	}

	public static Payload payloadFromFile(String path) {
		try {
			File file = new File(path);
			return Payload.fromFile(file);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			return null;
		}
	}

	public static String getPayloadFilePath(Payload payload) {
		Payload.File file = payload.asFile();
		if (file == null)
			return "";

		Uri uri = file.asUri();
		if (uri == null)
			return "";

		return uri.getPath();
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

	static PayloadCallback mPayloadCallback = new PayloadCallback() {
		@Override
		public void onPayloadReceived(@NonNull String endpointId, @NonNull Payload payload) {
			NearbyConnections.onPayloadReceived(endpointId, payload);
		}

		@Override
		public void onPayloadTransferUpdate(@NonNull String endpointId, @NonNull PayloadTransferUpdate payloadTransferUpdate) {
			NearbyConnections.onPayloadTransferUpdate(endpointId, payloadTransferUpdate);
		}
	};
}