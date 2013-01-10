//
//  ViewController.m
//  Controller
//
//  Created by Yaadhav Raaj on 17/12/12.
//  Copyright (c) 2012 Yaadhav Raaj. All rights reserved.
//

#import "ViewController.h"
#include "UDP.h"

@interface ViewController ()

@end

@implementation ViewController

@synthesize xLabel;
@synthesize xSlider;
@synthesize yLabel;
@synthesize ySlider;

//Send speed response to Car
-(void)SendResponse{
    
    if(X!=oldX || Y!=oldY){
        char *a=(char *)malloc(2);
        sprintf(a, "< X(%d) Y(%d) >\r", X,Y);
        printf(a);
        UDPSend(a);
    }
    
    oldX=X;
    oldY=Y;
}

//Update GUI with speeds
-(void)updateGUI{
    xLabel.text=[NSString stringWithFormat:@"%d",X];
    yLabel.text=[NSString stringWithFormat:@"%d",Y];
}

//Called when either slider value is changed
-(IBAction)updateX:(id)sender{
    UISlider* slider=sender;
    float x=slider.value;
    [self SendResponse];
    
    if(sender==xSlider){
        X=(int)x;
        slider.value=(float)X;
    }else if(sender==ySlider){
        Y=(int)x;
        slider.value=(float)Y;
    }
    [self updateGUI];
}

//Wait until the character r is received, then send r back
-(IBAction)connect:(id)sender{
    NSLog(@"waiting");
    UDPRec("r");
    char *a=(char *)malloc(2);
    a="r\r";
    UDPSend(a);
}

//Stop the Car by setting speeds to 0
-(IBAction)stop:(id)sender{
    X=0;
    Y=0;
    xSlider.value=0;
    ySlider.value=0;
    
    char *a=(char *)malloc(2);
    sprintf(a, "< X(%d) Y(%d) >\r", X,Y);
    
    printf(a);
    UDPSend(a);
    
    [self updateGUI];
}

//Initialize Port Values and set speeds to 0
- (void)viewDidLoad{
    UDPInit("172.20.10.9", "172.20.10.1", "50001", "50000");
    
    X=0;
    Y=0;
    [self updateGUI];
    [super viewDidLoad];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

@end
