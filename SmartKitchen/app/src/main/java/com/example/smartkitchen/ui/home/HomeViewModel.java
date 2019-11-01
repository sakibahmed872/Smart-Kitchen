package com.example.smartkitchen.ui.home;

import android.widget.ProgressBar;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

import com.example.smartkitchen.R;
import com.shinelw.library.ColorArcProgressBar;

public class HomeViewModel extends ViewModel {

    private MutableLiveData<String> mText;
    ColorArcProgressBar temp;

    public HomeViewModel() {
        mText = new MutableLiveData<>();
        mText.setValue("Welcome to Smart Kitchen");
    }

    public LiveData<String> getText() {
        return mText;
    }
}