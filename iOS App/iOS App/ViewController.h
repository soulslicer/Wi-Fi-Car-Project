//
//  ViewController.h
//  Controller
//
//  Created by Yaadhav Raaj on 17/12/12.
//  Copyright (c) 2012 Yaadhav Raaj. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController{
    
    int X;
    int Y;
    int oldX;
    int oldY;
}

//@property(nonatomic,strong)IBOutlet UIImageView* knob;
@property(nonatomic,strong)IBOutlet UILabel* xLabel;
@property(nonatomic,strong)IBOutlet UISlider* xSlider;
@property(nonatomic,strong)IBOutlet UILabel* yLabel;
@property(nonatomic,strong)IBOutlet UISlider* ySlider;

-(IBAction)updateX:(id)sender;
-(IBAction)connect:(id)sender;
-(IBAction)stop:(id)sender;



@end
