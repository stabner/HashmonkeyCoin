package com.HashmonkeyCoin.qt;

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
		final File HashmonkeyCoinDir = new File(getFilesDir().getAbsolutePath() + "/.HashmonkeyCoincore");
		if (!HashmonkeyCoinDir.exists()) {
			HashmonkeyCoinDir.mkdir();
		}


		super.onCreate(savedInstanceState);
	}
}
