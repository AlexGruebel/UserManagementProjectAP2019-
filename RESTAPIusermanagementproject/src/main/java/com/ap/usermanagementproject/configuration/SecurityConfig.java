package com.ap.usermanagementproject.configuration;

import java.util.Arrays;
import java.util.List;

import com.ap.usermanagementproject.repositories.UserPermissionRepository;
import com.ap.usermanagementproject.services.UMUserDetailService;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.access.AccessDecisionManager;
import org.springframework.security.access.AccessDecisionVoter;
import org.springframework.security.access.vote.AuthenticatedVoter;
import org.springframework.security.access.vote.RoleVoter;
import org.springframework.security.access.vote.UnanimousBased;
import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;
import org.springframework.security.config.http.SessionCreationPolicy;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.security.web.access.expression.WebExpressionVoter;
@EnableWebSecurity
@Configuration
public class SecurityConfig extends WebSecurityConfigurerAdapter {
   
    private UMUserDetailService userDetailService;
    private UserPermissionRepository userPermissionRepository;

    @Autowired
    public SecurityConfig(UMUserDetailService userDetailService, UserPermissionRepository userPermissionRepository){
        this.userDetailService = userDetailService;
        this.userPermissionRepository = userPermissionRepository;
    }
    
    @Override
    protected void configure(AuthenticationManagerBuilder auth) throws Exception {
       //auth.inMemoryAuthentication().withUser("user").password(encoder().encode("password")).roles("Admin").and().passwordEncoder(encoder());
       auth.userDetailsService(this.userDetailService).passwordEncoder(encoder());
    }
 
    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http.csrf().disable();
        http.httpBasic().authenticationEntryPoint(new RestAuthenticationEntryPoint());
        http.sessionManagement().sessionCreationPolicy(SessionCreationPolicy.STATELESS);
        http.authorizeRequests().anyRequest().authenticated().accessDecisionManager(accessDecisionManager());
    }

    @Bean
    public PasswordEncoder encoder() {
        return new BCryptPasswordEncoder();
    }

    
    public AccessDecisionManager accessDecisionManager() {
        List<AccessDecisionVoter<? extends Object>> decisionVoters 
          = Arrays.asList(
            new WebExpressionVoter(),
            new RoleVoter(),
            new AuthenticatedVoter(),
            new AccessDecisionRoleVoter(userPermissionRepository));
        return new UnanimousBased(decisionVoters);
    }

}