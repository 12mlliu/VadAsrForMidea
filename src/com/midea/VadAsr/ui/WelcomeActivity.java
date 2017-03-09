package com.midea.VadAsr.ui;

import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;

import com.midea.VadAsr.ui.R;
import com.midea.VadAsr.utils.IOToolkit;
import com.midea.VadAsr.utils.LogUtils;
import com.midea.VadAsr.utils.MideaVad;
import com.midea.VadAsr.utils.RecognizerUtils.ASrListener;

public class WelcomeActivity extends FragmentActivity implements ASrListener {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_welcome);
		// IOToolkit.ReInitialization(this, R.raw.model, this);
	}

	@Override
	protected void onResume() {
		super.onResume();
		IOToolkit.setAsrWask(this, R.raw.model, new ASrListener() {

			@Override
			public void onResults(String results) {
				startActivity(new Intent(WelcomeActivity.this, PageActivity.class));
				LogUtils.i("INFO:" + MideaVad.vadEnergyTht_sta + "   envEnergyBase:" + MideaVad.envEnergyBase);
			}

			@Override
			public void onError(String err) {
				// TODO Auto-generated method stub

			}

			@Override
			public void onAsrStart() {
				// TODO Auto-generated method stub

			}
		});
	}

	@Override
	public void onAsrStart() {

	}

	@Override
	public void onResults(String results) {
		startActivity(new Intent(this, PageActivity.class));
		// LogUtils.e("MideaVad.vadEnergyTht:" + MideaVad.vadEnergyTht);
		LogUtils.i("INFO:" + MideaVad.vadEnergyTht_sta + "   envEnergyBase:" + MideaVad.envEnergyBase);
	}

	@Override
	public void onError(String err) {

	}

}
