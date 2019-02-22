package com.ap.usermanagementproject.services;

import com.ap.usermanagementproject.entities.User;
import com.ap.usermanagementproject.entities.UserDetail;
import com.ap.usermanagementproject.entities.UserPrincipal;
import com.ap.usermanagementproject.repositories.UserDetailRepository;
import com.ap.usermanagementproject.repositories.UserRepository;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;

@Service
public class UMUserDetailService implements UserDetailsService {
 
    
    private UserDetailRepository userRepository;
 
    @Autowired
    public UMUserDetailService(UserDetailRepository userRepository){
        this.userRepository = userRepository;
    }

    @Override
    public UserDetails loadUserByUsername(String username) {
        UserDetail user = userRepository.findByUserName(username);
        
        if (user == null) {
            throw new UsernameNotFoundException(username);
        }
        
        return new UserPrincipal(user);
    }
}