package com.example.smartkitchen.ui.home;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProviders;

import com.akexorcist.roundcornerprogressbar.RoundCornerProgressBar;
import com.example.smartkitchen.R;
import com.github.lzyzsd.circleprogress.ArcProgress;
import com.github.lzyzsd.circleprogress.CircleProgress;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;
import com.shinelw.library.ColorArcProgressBar;

public class HomeFragment extends Fragment {

    private HomeViewModel homeViewModel;
    FirebaseDatabase database = FirebaseDatabase.getInstance();
    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        homeViewModel =
                ViewModelProviders.of(this).get(HomeViewModel.class);
        View root = inflater.inflate(R.layout.fragment_home, container, false);
        final TextView textView = root.findViewById(R.id.text_home);
        ColorArcProgressBar temp=root.findViewById(R.id.temp);
        ArcProgress dustbin=root.findViewById(R.id.arc_progress);
        TextView humidity=root.findViewById(R.id.humidity);
        RoundCornerProgressBar load1=root.findViewById(R.id.load_1);

        homeViewModel.getText().observe(this, new Observer<String>() {
            @Override
            public void onChanged(@Nullable String s) {
                textView.setText(s);
            }
        });

        if(FirebaseAuth.getInstance().getCurrentUser()!=null)
        {
            DatabaseReference myRef = database.getReference(FirebaseAuth.getInstance().getCurrentUser().getUid());
            temp_updater(myRef,temp);
            dustbin_updater(myRef,dustbin);
            humidity_updater(myRef,humidity);
            load_1_updater(myRef, load1 );


        }
        return root;
    }

    void temp_updater(DatabaseReference myRef, ColorArcProgressBar temp )
    {
        ValueEventListener postListener = new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                // Get Post object and use the values to update the UI
                temp.setCurrentValues(Float.parseFloat(dataSnapshot.getValue().toString()));
                // ...
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {
                // Getting Post failed, log a message
            }
        };
        myRef.child("sensor").child("temp").addValueEventListener(postListener);
    }

    void dustbin_updater(DatabaseReference myRef, ArcProgress dustbin )
    {
        ValueEventListener postListener = new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                // Get Post object and use the values to update the UI
                dustbin.setProgress(Integer.parseInt(dataSnapshot.getValue().toString()));
                // ...
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {
                // Getting Post failed, log a message
            }
        };
        myRef.child("sensor").child("dustbin").addValueEventListener(postListener);
    }

    void humidity_updater(DatabaseReference myRef, TextView humidity)
    {
        ValueEventListener postListener = new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                // Get Post object and use the values to update the UI
                humidity.setText(dataSnapshot.getValue().toString());
                // ...
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {
                // Getting Post failed, log a message
            }
        };
        myRef.child("sensor").child("Humidity").addValueEventListener(postListener);
    }

    void load_1_updater(DatabaseReference myRef, RoundCornerProgressBar load1 )
    {
        ValueEventListener postListener = new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                // Get Post object and use the values to update the UI
                load1.setProgress(Float.parseFloat(dataSnapshot.getValue().toString()));
                // ...
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {
                // Getting Post failed, log a message
            }
        };
        myRef.child("sensor").child("load1").addValueEventListener(postListener);
    }

}