package com.hashmonkeycoin.qt;

import android.os.Bundle;
import android.system.ErrnoException;
import android.system.Os;

import org.qtproject.qt5.android.bindings.QtActivity;

import java.io.File;

public class HashmonkeyCoinQtActivity extends QtActivity
{
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		final File hashmonkeycoinDir = new File(getFilesDir().getAbsolutePath() + "/.hashmonkeycoin");
		if (!hashmonkeycoinDir.exists()) {
			hashmonkeycoinDir.mkdir();
		}


		super.onCreate(savedInstanceState);
	}
}